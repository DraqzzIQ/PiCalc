chars = []
while True:
    inp = input("next Char: ")
    if inp == "esc":
        break
    if inp == "":
        inp = "ADD VALUE !!!"
    chars.append(inp)

out = ""
for i, c in enumerate(chars):
    out += "\t{ \"" + c + "\", " + str(i+69) + " },\n"

print(out)