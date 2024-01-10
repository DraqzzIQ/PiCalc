import pyperclip

with open("Keymap.txt", "r") as k:
    keymap = {line[3:-3].split("\", ")[0]: int(line[3:-3].split("\", ")[1]) for line in k.read().split("\n")}

while True:
    chars = []
    inp = input("input: ")
    if inp == "":
        break

    i = 0
    while i < len(inp):
        if inp[i] == "\\":
            num = ""
            i += 1
            while i < len(inp) and inp[i] != "\\":
                num += inp[i]
                i += 1
            if num != "":
                if num.isnumeric():
                    chars.append(int(num))
                else:
                    chars.append(keymap[num])
        else:
            chars.append(keymap[inp[i]])
        i += 1

    res = "KEY_SET" + str(chars).replace("[", "{").replace("]", "}")
    print(res)
    pyperclip.copy(res)