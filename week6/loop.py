word = input("Say a word: ")
i = 0
n = 3
while i < n:
    print(word)
    i+=1
print("\n")

for _ in [0,1,2]:
    print(word)
print("\n")

for _ in range(n):
    print(f"{word.upper()} ", end="")
print("\n")

for s in ["juan","pedro","culo"]:
    print(s)

