import tkinter as tk
import math


def motion(event):
    global draw, w
    if 0 <= event.x < width*50 and 0 <= event.y < height*50:
        w.itemconfig(fields[math.floor(event.x/50)][math.floor(event.y/50)], fill="black" if draw else "white")


def tool(event):
    global draw
    draw = not draw


def save():
    print(str([[w.itemcget(fields[x][y], "fill") == "black" for y in range(height)] for x in range(width)]).lower().replace("[", "{").replace("]", "}"))
    root.destroy()


fields = []
draw = True
# width = int(input("width"))
# height = int(input("height"))
width = 10
height = 10
root = tk.Tk()
root.geometry(f"{width*50}x{height*50}")
w = tk.Canvas(root, width=width*50, height=height*50, bg="grey")

for x in range(width):
    fields.append([])
    for y in range(height):
        fields[x].append(w.create_rectangle(x*50+5, y*50+5, x*50+45, y*50+45, fill="white"))
        pass

w.bind("<ButtonPress-1>", motion)
w.bind("<B1-Motion>", motion)
root.bind("<space>", tool)
root.bind("<Escape>", save)
root.protocol("WM_DELETE_WINDOW", save)
w.pack()
root.mainloop()