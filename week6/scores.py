from cs50 import get_int

scores = []

for i in range(3):
    x = get_int("Score: ")
    scores.append(x)

average = sum(scores) / len(scores)
print(f"Average: {average}")
