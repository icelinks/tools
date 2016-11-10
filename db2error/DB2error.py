#usr/bin/env python3
#-*- coding:UTF-8 -*-

import sqlite3
import tkinter as tk
from tkinter import *
from tkinter import messagebox

root = Tk()
root.resizable(False,False)
root.title("DBerror")

def Search():
	id = (ey.get(),)
	cx = sqlite3.connect("error.db")
	cu = cx.cursor()
	cu.execute("select * from DBerror where id = ?",id)
	r = cu.fetchone()
	messagebox.askokcancel(title="result",message=r[1])
	
bt = tk.Button(root,text = "查询",command = Search)
bt.grid(column = 1,row = 0)
ey = tk.Entry(root,text = "")
ey.grid(column = 0,row = 0)

root.update() # update window ,must do
curWidth = root.winfo_reqwidth() # get current width
curHeight = root.winfo_height() # get current height
scnWidth,scnHeight = root.maxsize() # get screen width and height
# now generate configuration information
tmpcnf = '%dx%d+%d+%d'%(curWidth,curHeight,
(scnWidth-curWidth)/2,(scnHeight-curHeight)/2)
root.geometry(tmpcnf)	

root.mainloop()