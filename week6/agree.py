answer = input("Do you agree? ").lower()

if answer in ["y","yes"]:
    print("Agreed")
elif answer in ["n","no"]:
    print("Disagreed")
else:
    print("Answer not supported")
