import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    companies = db.execute("SELECT symbol, amount FROM shares WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total = 0
    for company in companies:
        price = lookup(company["symbol"])["price"]
        company["price"] = usd(price)
        holding = price * company["amount"]
        company["holding"] = usd(holding)
        total += holding

    total += cash
    return render_template("view.html", companies = companies, cash = usd(cash), total = usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide a stock’s symbol", 400)
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Invalid Number of Shares", 400)
        if shares < 1:
            return apology("Invalid Number of Shares", 400)
        info = lookup(symbol)
        if not info:
            return apology("SYMBOL NOT FOUND", 400)

        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        shares_owened = db.execute("SELECT symbol, amount FROM shares WHERE user_id = ? AND symbol = ?", session["user_id"], info["symbol"])

        if info["price"] * shares > user[0]["cash"]:
            return apology("NOT ENOUGH CASH", 403)

        date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        db.execute("INSERT INTO transactions (user_id, symbol, amount, action, price, date) VALUES(?, ?, ?, ?, ?, ?)", session["user_id"], info["symbol"], shares, "buy", usd(info["price"]), date)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user[0]["cash"] - info["price"] * shares, session["user_id"])

        if not shares_owened:
            db.execute("INSERT INTO shares (user_id, symbol, amount) VALUES(?, ?, ?)", session["user_id"], info["symbol"], shares)
        elif shares_owened[0]["symbol"] == info["symbol"]:
            db.execute("UPDATE shares SET amount = ? WHERE user_id = ? AND symbol = ?", shares_owened[0]["amount"] + shares, session["user_id"], info["symbol"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY date DESC", session["user_id"])
    return render_template("history.html", transactions = transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a stock’s symbol", 400)

        info = lookup(request.form.get("symbol"))
        if not info:
            return apology("NOT FOUND", 400)
        info["price"] = usd(info["price"])
        return render_template("quoted.html", info = info)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
        except ValueError:
            return apology("username already in use", 400)
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide a stock’s symbol", 400)
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Invalid Number of Shares", 400)
        if shares < 1:
            return apology("Invalid Number of Shares", 400)
        info = lookup(symbol)
        if not info:
            return apology("SYMBOL NOT FOUND", 400)
##
        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        shares_owened = db.execute("SELECT symbol, amount FROM shares WHERE user_id = ? AND symbol = ?", session["user_id"], info["symbol"])

        if not shares_owened:
            return apology("share not owened", 400)
        if shares > shares_owened[0]["amount"]:
            return apology("not enough shares to sell", 400)

        date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        db.execute("INSERT INTO transactions (user_id, symbol, amount, action, price, date) VALUES(?, ?, ?, ?, ?, ?)", session["user_id"], info["symbol"], shares, "sell", usd(info["price"]), date)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user[0]["cash"] + info["price"] * shares, session["user_id"])
        if shares_owened[0]["amount"] - shares == 0:
            db.execute("DELETE FROM shares WHERE user_id = ? AND symbol = ?", session["user_id"], info["symbol"])
        else:
            db.execute("UPDATE shares SET amount = ? WHERE user_id = ? AND symbol = ?", shares_owened[0]["amount"] - shares, session["user_id"], info["symbol"])

        return redirect("/")

    else:
        shares = db.execute("SELECT symbol FROM shares WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", shares = shares)

@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Buy shares of stock"""
    if request.method == "POST":
        try:
            new_cash = float(request.form.get("cash"))
        except ValueError:
            return apology("Invalid Number of Cash", 403)
        if new_cash < 1:
            return apology("Invalid Number of Cash", 403)

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash[0]["cash"] + new_cash, session["user_id"])
        return redirect("/")

    else:
        return render_template("cash.html")
