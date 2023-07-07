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
    print(str([[1 if w.itemcget(fields[x][y], "fill") == "black" else 0 for y in range(height)] for x in range(width)]).
          replace("[", "{").replace("]", "}"))
    print()


def close():
    save(0)
    root.destroy()


def updateSize(event):
    global cell_size, fields, padding
    cell_size = min(math.floor(root.winfo_width()/width), math.floor(root.winfo_height()/height))
    padding = cell_size // 10

    w.config(width=width * cell_size, height=height * cell_size)

    for x in range(width):
        for y in range(height):
            w.coords(fields[x][y], x * cell_size + padding, y * cell_size + padding, x * cell_size + cell_size - padding, y * cell_size + cell_size - padding)


def addColumn(event):
    global width
    width += 1
    fields.append([w.create_rectangle(0, 0, 0, 0, fill="white") for _ in range(height)])
    updateSize(0)


def removeColumn(event):
    global width
    if width > 1:
        width -= 1
        for y in range(height-1, -1, -1):
            print(y)
            w.delete(fields[-1][y])
        del fields[-1]
        updateSize(0)
        print(fields, height)


def addRow(event):
    global height
    height += 1
    for x in range(width):
        fields[x].append(w.create_rectangle(0, 0, 0, 0, fill="white"))
    updateSize(0)


def removeRow(event):
    global height
    if height > 1:
        height -= 1
        for x in range(width):
            w.delete(fields[x][-1])
            del fields[x][-1]
        updateSize(0)
        print(fields, height)


def increaseSize(event):
    global size
    size += 1


def decreaseSize(event):
    global size
    size -= 1


root = tk.Tk()
root.withdraw()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
root.geometry(f"{screen_width//2}x{screen_height//2}")
w = tk.Canvas(root, width=0, height=0, bg="grey")


draw = True
size = 1
fields = []
width = input("width / import: ")
try:
    width = int(width)
    height = int(input("height: "))
    for x in range(width):
        fields.append([])
        for y in range(height):
            fields[x].append(w.create_rectangle(0, 0, 0, 0, fill="white"))
except ValueError:
    importList = [["black" if b == "1" else "white" for b in l.split(", ")] for l in width[2:-2].split("}, {")]
    width = len(importList)
    height = len(importList[0])

    for x in range(width):
        fields.append([])
        for y in range(height):
            fields[x].append(w.create_rectangle(0, 0, 0, 0, fill=importList[x][y]))


w.bind("<ButtonPress-1>", motion)
w.bind("<B1-Motion>", motion)
root.bind("<space>", tool)
root.bind("<Escape>", save)
root.bind("<Configure>", updateSize)
root.bind("<Right>", addColumn)
root.bind("<Left>", removeColumn)
root.bind("<Down>", addRow)
root.bind("<Up>", removeRow)
root.bind("<plus>", increaseSize)
root.bind("<minus>", decreaseSize)
root.protocol("WM_DELETE_WINDOW", close)
w.pack()
root.wm_deiconify()
root.mainloop()