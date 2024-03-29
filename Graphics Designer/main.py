import tkinter as tk
from math import floor
from pyperclip import copy


def motion(event):
    if 0 <= event.x < width * cell_size and 0 <= event.y < height * cell_size:
        start_x = floor(event.x / cell_size)
        start_y = floor(event.y / cell_size)
        for delta_x in range(pen_size):
            for delta_y in range(pen_size):
                if start_x + delta_x < width and start_y + delta_y < height:
                    w.itemconfig(fields[start_x + delta_x][start_y + delta_y], fill="black" if draw else "white")


def changeTool(event):
    global draw
    draw = not draw


def updateCellSize(event):
    global fields, cell_size, padding
    cell_size = min(floor(root.winfo_width()/width), floor(root.winfo_height()/height))
    padding = cell_size // 10

    w.config(width=width * cell_size, height=height * cell_size)

    for cx in range(width):
        for cy in range(height):
            w.coords(fields[cx][cy], cx * cell_size + padding, cy * cell_size + padding, cx * cell_size + cell_size - padding, cy * cell_size + cell_size - padding)


def addColumn(event):
    global width
    width += 1
    fields.append([w.create_rectangle(0, 0, 0, 0, fill="white") for _ in range(height)])
    updateCellSize(0)


def removeColumn(event):
    global width
    if width > 1:
        width -= 1
        for cy in range(height-1, -1, -1):
            print(cy)
            w.delete(fields[-1][cy])
        del fields[-1]
        updateCellSize(0)
        print(fields, height)


def addRow(event):
    global height
    height += 1
    for cx in range(width):
        fields[cx].append(w.create_rectangle(0, 0, 0, 0, fill="white"))
    updateCellSize(0)


def removeRow(event):
    global height
    if height > 1:
        height -= 1
        for cx in range(width):
            w.delete(fields[cx][-1])
            del fields[cx][-1]
        updateCellSize(0)
        print(fields, height)


def increasePenSize(event):
    global pen_size
    pen_size += 1


def decreasePenSize(event):
    global pen_size
    pen_size -= 1


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


def getString():
    output = [["1" if w.itemcget(fields[cx][cy], "fill") == "black" else "0" for cy in range(height)] for cx in range(width)]
    output_str = f"{{ {name}, Bitset2D({width}, {height}, {{"
    for row in output:
        row.extend("0" * 7)
        output_str += "{"
        for i in range(0, len(row) - 7, 8):
            output_str += "0b" + "".join(row[i:i + 8]) + ", "
        output_str = output_str[:-2]
        output_str += "}, "
    output_str = output_str[:-2] + "})}, "
    return output_str


def save(event):
    output_str = getString()
    print(output_str)
    copy(output_str)


def close():
    save(0)
    root.destroy()


def reopen(event):
    global name
    global fields
    output_str = getString()
    file.write(output_str + "\n")
    name += 1
    print("name: " + str(name))

    for cx in range(width):
        for cy in range(height):
            w.itemconfig(fields[cx][cy], fill="white")


def reopen_unknown(event):
    global name
    global fields
    output_str = getString()
    file.write(output_str + "//?\n")
    name += 1
    print("name: " + str(name))

    for cx in range(width):
        for cy in range(height):
            w.itemconfig(fields[cx][cy], fill="white")


def close_multiple():
    reopen(0)
    root.destroy()


root = tk.Tk()
root.withdraw()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
root.geometry(f"{screen_width//2}x{screen_height//2}+{500}+{20}")
w = tk.Canvas(root, width=0, height=0, bg="grey")

draw = True
pen_size = 1
cell_size = 0
padding = 0
fields = []

start_type = input("start type? (1 = single width + height, 2 = import, 3 = multiple): ")
# start_type = "1"

if start_type == "1":
    name = input("name: ")
    width = int(input("width: "))
    height = int(input("height: "))

    # width = 5
    # height = 9

    start(width, height)

    root.bind("<Escape>", save)
    root.bind("<Return>", save)
    root.protocol("WM_DELETE_WINDOW", close)

elif start_type == "2":
    print("not working yet")
    # TODO
    # importListRaw = input("input List: ")
    # importList = [["black" if b == "1" else "white" for b in l.split(", ")] for l in importListRaw[2:-2].split("}, {")]
    # width = len(importList)
    # height = len(importList[0])
    #
    # fields = []
    # for x in range(width):
    #     fields.append([])
    #     for y in range(height):
    #         fields[x].append(w.create_rectangle(0, 0, 0, 0, fill=importList[x][y]))
    #
    # root.bind("<Escape>", save)
    # root.bind("<Return>", save)
    # root.protocol("WM_DELETE_WINDOW", close)

elif start_type == "3":
    name = int(input("start name: "))
    width = int(input("width: "))
    height = int(input("height: "))

    start(width, height)

    file = open("result.txt", "w")

    root.bind("<Escape>", reopen_unknown)
    root.bind("<Return>", reopen)
    root.protocol("WM_DELETE_WINDOW", close_multiple)

else:
    print("please enter a valid mode")
    exit()


w.bind("<ButtonPress-1>", motion)
w.bind("<B1-Motion>", motion)
root.bind("<space>", changeTool)
root.bind("<Configure>", updateCellSize)
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