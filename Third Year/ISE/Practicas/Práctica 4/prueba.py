#!/usr/bin/env python
# -*- coding:utf-8 -*-

from sys import argv
import subprocess
import time

import tkinter as tk
root = tk.Tk()
root.title("BENCHMARK WEB LANGUAGES")
photo = tk.PhotoImage(file= r"writefile.gif")
photo2 = tk.PhotoImage(file = r"readfile.gif")
photo3 = tk.PhotoImage(file = r"bubblesortbenchmark.gif")
cv = tk.Canvas(root,width=2000, height=2000)
cv.pack(side='top', fill='both', expand='yes')
cv.create_text(950,100,font=("Purisa", 50),text = "BENCHMARK WEB LANGUAGES")
cv.create_image(5, 200, image=photo, anchor='nw')
cv.create_image(645, 200, image=photo2, anchor='nw')
cv.create_image(1280, 200, image=photo3, anchor='nw')
root.mainloop()
