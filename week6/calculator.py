x = int(input("give a number "))
y = int(input("give another number "))
z = 1/3

print("The result is:", x + y)

print(f"The result is: {x + y}")

if x > y:
    print(f"{x} is grater then {y}")
elif y > x:
    print(f"{x} is less then {y}")
else:
    print(f"{x} and {y} are equal")


print(f"{z:.50f}")
