import tkinter as tk
import math

def motion(event):
    global draw, w
    if 0 <= event.x < width * cell_size and 0 <= event.y < height * cell_size:
        w.itemconfig(fields[math.floor(event.x / cell_size)][math.floor(event.y / cell_size)], fill="black" if draw else "white")

def tool(event):
    global draw
    draw = not draw

def save():
    print(str([[w.itemcget(fields[x][y], "fill") == "black" for y in range(height)] for x in range(width)]).lower().replace("[", "{").replace("]", "}"))
    root.destroy()

fields = []
draw = True
width = int(input("width"))
height = int(input("height"))

root = tk.Tk()

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

cell_size = min((screen_width - 100) // width, (screen_height - 100) // height)

root.geometry(f"{width * cell_size}x{height * cell_size}")
w = tk.Canvas(root, width=width * cell_size, height=height * cell_size, bg="grey")

for x in range(width):
    fields.append([])
    for y in range(height):
        padding = 5 * (cell_size // 50)
        fields[x].append(w.create_rectangle(x * cell_size + padding, y * cell_size + padding, x * cell_size + cell_size - padding, y * cell_size + cell_size - padding, fill="white"))

w.bind("<ButtonPress-1>", motion)
w.bind("<B1-Motion>", motion)
root.bind("<space>", tool)
root.bind("<Escape>", save)
root.protocol("WM_DELETE_WINDOW", save)
w.pack()
root.mainloop()