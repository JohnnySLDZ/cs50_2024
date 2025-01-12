people = [
    {"name": "juan", "color": "rojo"},
    {"name": "pedro", "color": "marron"},
    {"name": "andres", "color": "blanco"},
]

name = input("Name of the person: ")

for person in people:
    if person["name"] == name:
        print(f"\n{name} have been found\n")
        print(f"Their favorite color is: {person['color']}")
        break
else:
    print("Not found")
