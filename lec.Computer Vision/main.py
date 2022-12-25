from tkinter import * 
from PIL import ImageTk,Image
import cv2
import numpy as np
from PIL import *

global label
global original
global img
global gray_img

def event():
    label.config(text = "Original")
    windowImg.config(image=original)
    windowImg.image=original
def event1():
    label.config(text = "Mean(3*3) Filtering")
    kernel=np.ones((3,3),np.float32)/9
    output=cv2.filter2D(gray_img,-1,kernel)
    output_img=Image.fromarray(output)
    final=ImageTk.PhotoImage(image=output_img)
    windowImg.config(image=final)
    windowImg.image=final
def event2():
    label.config(text = "Mean(5*5) Filtering")
    kernel=np.ones((5,5),np.float32)/25
    output=cv2.filter2D(gray_img,-1,kernel)
    output_img=Image.fromarray(output)
    final=ImageTk.PhotoImage(image=output_img)
    windowImg.image=final
    windowImg.config(image=final)
def event3():
    label.config(text = "Median(3*3) Filtering")
    output=cv2.medianBlur(gray_img,3)
    output_img=Image.fromarray(output)
    final=ImageTk.PhotoImage(image=output_img)
    windowImg.image=final
    windowImg.config(image=final)
def event4():
    label.config(text = "Median(5*5) Filtering")
    output=cv2.medianBlur(gray_img,5)
    output_img=Image.fromarray(output)
    final=ImageTk.PhotoImage(image=output_img)
    windowImg.image=final
    windowImg.config(image=final)
def event5():
    label.config(text = "Laplacian(3*3) Filtering")
    output=cv2.Laplacian(gray_img, 3)
    output_img=Image.fromarray(output)
    final=ImageTk.PhotoImage(image=output_img)
    windowImg.image=final
    windowImg.config(image=final)

window=Tk()
window.title("vision HW1")
button=Button(window, text='original', command=event)
button1 = Button(window, text='Mean(3*3) Filtering.', command=event1)
button2 = Button(window, text='Mean(5*5) Filtering', command=event2)
button3 = Button(window, text='Median(3*3) Filtering.', command=event3)
button4 = Button(window, text='Median(5*5) Filtering', command=event4)
button5 = Button(window, text='Laplacian(3*3) Filtering.', command=event5)

img=PhotoImage(file="C:\\Users\\Master\\Desktop\\python project\\origin.PNG")
original=img
windowImg=Label(window, image=img)
windowImg.pack(expand=1, anchor=CENTER)


tmp=cv2.imread("C:\\Users\\Master\\Desktop\\python project\\origin.PNG")
gray_img=cv2.cvtColor(tmp,cv2.COLOR_BGR2GRAY)

label = Label(window, text = "Original")
label.pack()

button.pack(side=LEFT, padx=10, pady=10)
button1.pack(side=LEFT, padx=10, pady=10)
button2.pack(side=LEFT, padx=10, pady=10)
button3.pack(side=LEFT, padx=10, pady=10)
button4.pack(side=LEFT, padx=10, pady=10)
button5.pack(side=LEFT, padx=10, pady=10)

window.mainloop()