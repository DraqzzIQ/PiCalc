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
    out += "\t{ \"" + c + "\", " + str(i+190) + " },\n"

print(out)
print(chars)
