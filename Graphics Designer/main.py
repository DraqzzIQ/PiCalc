import tkinter as tk
import math


def motion(event):
    if 0 <= event.x < width * cell_size and 0 <= event.y < height * cell_size:
        start_x = math.floor(event.x / cell_size)
        start_y = math.floor(event.y / cell_size)
        for delta_x in range(size):
            for delta_y in range(size):
                if start_x + delta_x < width and start_y + delta_y < height:
                    w.itemconfig(fields[start_x + delta_x][start_y + delta_y], fill="black" if draw else "white")


def tool(event):
    global draw
    draw = not draw


def save(event):
    # saveString = str([[1 if w.itemcget(fields[cx][cy], "fill") == "black" else 0 for cy in range(height)] for cx in range(width)]).replace("[", "{").replace("]", "}")
    output = [["1" if w.itemcget(fields[cx][cy], "fill") == "black" else "0" for cy in range(height)] for cx in range(width)]
    output_str = []
    print(output)
    for cx in range(width):
        for i in range(7-((height-1) % 8)):
            output[cx].append("0")
        output_str.append("".join(output[cx]))

    for cx in output_str:
        print(str([("0b" + cx[i:i+8]) for i in range(0, len(cx), 8)]).replace("[", "{").replace("]", "}").replace("'", ""), end=", ")
    # print(output_str)
    # saveString = str()
    # print(saveString + "\n")
    # pyperclip.copy("\t{ " + name + ", " + saveString + "},")

def close():
    save(0)
    root.destroy()


def updateSize(event):
    global fields, cell_size, padding
    cell_size = min(math.floor(root.winfo_width()/width), math.floor(root.winfo_height()/height))
    padding = cell_size // 10

    w.config(width=width * cell_size, height=height * cell_size)

    for cx in range(width):
        for cy in range(height):
            w.coords(fields[cx][cy], cx * cell_size + padding, cy * cell_size + padding, cx * cell_size + cell_size - padding, cy * cell_size + cell_size - padding)


def addColumn(event):
    global width
    width += 1
    fields.append([w.create_rectangle(0, 0, 0, 0, fill="white") for _ in range(height)])
    updateSize(0)


def removeColumn(event):
    global width
    if width > 1:
        width -= 1
        for cy in range(height-1, -1, -1):
            print(cy)
            w.delete(fields[-1][cy])
        del fields[-1]
        updateSize(0)
        print(fields, height)


def addRow(event):
    global height
    height += 1
    for cx in range(width):
        fields[cx].append(w.create_rectangle(0, 0, 0, 0, fill="white"))
    updateSize(0)


def removeRow(event):
    global height
    if height > 1:
        height -= 1
        for cx in range(width):
            w.delete(fields[cx][-1])
            del fields[cx][-1]
        updateSize(0)
        print(fields, height)


def increasePenSize(event):
    global size
    size += 1


def decreasePenSize(event):
    global size
    size -= 1


def start(width_in, height_in):
    global width
    global height
    global fields

    width = width_in
    height = height_in
    fields = []

    for cx in range(width):
        fields.append([])
        for cy in range(height):
            fields[cx].append(w.create_rectangle(0, 0, 0, 0, fill="white"))


def reopen(event):
    global name
    global width
    global height
    global fields

    saveString = str([[1 if w.itemcget(fields[cx][cy], "fill") == "black" else 0 for cy in range(height)] for cx in range(width)]).replace("[", "{").replace("]", "}")
    file.write("\t{ " + str(name) + ", " + saveString + "},\n")

    for cx in range(width):
        fields.append([])
        for cy in range(height):
            w.itemconfig(fields[cx][cy], fill="white")

    # start(width, height)
    name += 1

    print("name: " + str(name))


def close_multiple():
    reopen(0)
    root.destroy()


def reopen_unknown(event):
    global name
    global width
    global height
    global fields

    saveString = str([[1 if w.itemcget(fields[cx][cy], "fill") == "black" else 0 for cy in range(height)] for cx in range(width)]).replace("[", "{").replace("]", "}")
    file.write("\t{ " + str(name) + ", " + saveString + "}, //?\n")


    for cx in range(width):
        fields.append([])
        for cy in range(height):
            w.itemconfig(fields[cx][cy], fill="white")

    # start(width, height)
    name += 1

    print("name: " + str(name))


root = tk.Tk()
root.withdraw()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
root.geometry(f"{screen_width//2}x{screen_height//2}+{500}+{20}")
w = tk.Canvas(root, width=0, height=0, bg="grey")


draw = True
size = 1
fields = []
start_type = input("start type? (1 = single width + height, 2 = import, 3 = multiple): ")

if start_type == "1":
    name = input("name: ")
    width = int(input("width: "))
    height = int(input("height: "))

    # width = 5
    # height = 9
    start(width, height)

    root.bind("<Escape>", save)
    root.protocol("WM_DELETE_WINDOW", close)

elif start_type == "2":
    importListRaw = input("input List: ")
    importList = [["black" if b == "1" else "white" for b in l.split(", ")] for l in importListRaw[2:-2].split("}, {")]
    width = len(importList)
    height = len(importList[0])

    fields = []
    for x in range(width):
        fields.append([])
        for y in range(height):
            fields[x].append(w.create_rectangle(0, 0, 0, 0, fill=importList[x][y]))

    root.bind("<Escape>", save)
    root.protocol("WM_DELETE_WINDOW", close)

elif start_type == "3":
    name = int(input("start name: "))
    width = int(input("width: "))
    height = int(input("height: "))

    # name = 16
    # width = 5
    # height = 9

    start(width, height)

    file = open("result.txt", "w")

    root.bind("<Escape>", reopen_unknown)
    root.bind("<Return>", reopen)
    root.protocol("WM_DELETE_WINDOW", close_multiple)


w.bind("<ButtonPress-1>", motion)
w.bind("<B1-Motion>", motion)
root.bind("<space>", tool)
root.bind("<Configure>", updateSize)
root.bind("<Right>", addColumn)
root.bind("<Left>", removeColumn)
root.bind("<Down>", addRow)
root.bind("<Up>", removeRow)
root.bind("<plus>", increasePenSize)
root.bind("<minus>", decreasePenSize)
w.pack()
root.wm_deiconify()
root.lift()
root.mainloop()