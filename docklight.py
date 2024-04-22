from tkinter import *
from tkinter import messagebox
import tkinter.ttk as ttk
import tkinter as tk

import serial
import time
import serial.tools.list_ports
import datetime

#arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
#time.sleep(2)
#arduino.reset_input_buffer()

rcv_addr = 8

top = Tk()
top.geometry("640x480")

connected = False

# --- functions ---

def sendGoal():
    global connected, arduino
    
    if connected:
        mensaje = msg_entry.get()
        arduino.write(mensaje.encode())
        msg=messagebox.showinfo( "Mensaje", mensaje)

def serial_ports():    
    return serial.tools.list_ports.comports()

def on_select(event=None):
    global connected, arduino
    
    # get selection from event    
    print("event.widget:", event.widget.get())

    # or get selection directly from combobox
    arduino = serial.Serial(cb.get().partition(' ')[0], 115200, timeout=1)
    connected = True
    print("comboboxes: ", cb.get().partition(' ')[0])

def receive_data():
    global connected, arduino
    if connected:
        line = arduino.readline()
        if line:
            string = line.decode()  # convert the byte string to a unicode string
            rcv.insert(tk.END, string)
    top.after(1000,receive_data)
    return


# --- main ---

# serial port combobox
cb = ttk.Combobox(top, values=serial_ports())
cb.pack()
cb.place(x=450,y=5)

# send message textbox
msg_label = Label(top, text="Mensaje")
msg_label.place(x=10,y=5)
#L1.pack( side = LEFT)
msg_entry = Entry(top, bd =5)
msg_entry.place(x=80,y=0)
#E1.pack(side = LEFT)
B = Button(top, text ="Enviar", command = sendGoal)
B.place(x=50,y=50)

# receive message
S = tk.Scrollbar(top)
rcv = tk.Text(height = 4, width = 640)


S.pack(side=RIGHT)
rcv.pack(side=tk.BOTTOM)

S.config(command=rcv.yview)
#S.pack(side=tk.BOTTOM)
rcv.config(yscrollcommand=S.set)


# assign function to combobox
cb.bind('<<ComboboxSelected>>', on_select)

receive_data()


top.mainloop()