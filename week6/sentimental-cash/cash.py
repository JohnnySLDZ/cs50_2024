from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

coins = [0.25,0.10,0.05,0.01]
cash = 0
i = 0
while change > 0:
    if change - coins[i] >= 0:
        change = round((change - coins[i]),2)
        cash += 1
    else:
        i+=1


print(cash)
