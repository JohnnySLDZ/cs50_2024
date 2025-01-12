from cs50 import get_int

height = 0
while True:
    height = get_int("Height for the piramid: ")
    if height > 0 and height <= 8:
        break
for i in range(height+1)[1:]:
    print(" " * (height-i) + "#" * i + "  ", end="")
    print("#" * i)



