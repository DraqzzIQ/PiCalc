with open("Keymap.txt", "r") as k:
    keymap = {line[3:-3].split("\", ")[0]: int(line[3:-3].split("\", ")[1]) for line in k.read().split("\n")}

chars = []
while True:
    inp = input("input: ")
    if inp == "":
        break

    for char in inp:
        chars.append(keymap[char])
print("KEY_SET" + str(chars).replace("[", "{").replace("]", "}"))