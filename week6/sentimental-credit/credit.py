import re
from cs50 import get_int

number = get_int("Card number: ")
number = str(number)


americanExpress = re.findall("^[3][4-7]", number)
masterCard = re.findall("^[5][1-5]", number)
visa = re.findall("^4", number)

number = list(number)
number = [int(i) for i in number]


pairs = []
others = []


for i in range(len(number)):
    if i % 2 == 0:
        if number[i]*2 >= 10:
            x = str(number[i]*2)
            y = 0
            for j in x:
                y += int(j)
            pairs.append(y)
        else:
            pairs.append(number[i]*2)
    else:
        others.append(number[i])


result = str(sum(pairs)+sum(others))
print(result)

if result[len(result)-1] == '0':
    if americanExpress:
        print("AMEX")
    if masterCard:
        print("MASTERCARD")
    if visa:
        print("VISA")
else:
    print("INVALID")

