ret = []

for x in range(6):
    for y in range(9):
        inp = input(f"x {x}\ty {y}:")
        if inp != "":
            ret.append((x*10+y, inp))

for r in ret:
    print(f"\t\tcase {r[0]:02d}: return Chars::KEY_MAP.at(\"{r[1]}\");")