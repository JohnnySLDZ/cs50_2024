def main():
    x = get_int("Give me a number: ")
    y = get_int("Another number: ")

    print(f"x + y = {x + y}")


def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Not an Int")

main()
