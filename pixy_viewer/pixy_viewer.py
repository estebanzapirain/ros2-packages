#!/usr/bin/env python

"""\
Pixy SPI Viewer
Gets data from ROSArduinoPixyBridge through command 'm'. Displays data on canvas.


"""

#Import libraries
import tkinter as tk
import serial
import time

# init serial comm
arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
arduino.reset_input_buffer()
time.sleep(1)

# Create the main window
window = tk.Tk()
window.geometry("640x480")
window.title("PixyCam SPI Viewer")
# window['background'] = 'black'

# Dimensions
w = 640
h = 480
scale = w / 320 #Scale factor relative to 320x240

# Create a Canvas widget
canvas_1 = tk.Canvas(window, width=w, height=h)
canvas_1.pack()

# Frames per second
fps = 4

# Quantity of blocks expected, used to decide if data is valid
BLOCKS_EXPECTED = 4
BLOCK_LENGTH = 6

while 1:
    
    data = [] # init empty data structure
    
    arduino.write(b'ID01m\r\n') # send command "m" (GET_MAP) trough serial port
    
    blocks = 0
    
    # READ DATA
    while arduino.in_waiting>0: # while there's data available
        str = arduino.readline().rstrip() # read incoming line and throw away ending \r\n
        data.append(str) # add line to existing data
        blocks += 1
#        print(str)
    print(blocks) # print quantity of blocks
    if blocks >= BLOCKS_EXPECTED:  # if data is valid
        canvas_1.delete('all') #clear canvas
    
    
    # PROCESS DATA    
    for block in data: #for each block
        if (len(block)>0): #if there is data
  
            if block[0] == 73: #if begins with IDxx, data starts at index 4
                start = 4
            else:
                start = 0
#           print(len(block))
#           print(start)
#            print(block)
            if len(block)>=start + BLOCK_LENGTH: #check length of data    
                
                #split block
                sig = block[start]
                
                #x range exceeds 8 bits, so it comes divided into 2 bytes
                #MSB is 'S' if x exceeds 256
                if block[start + 1] == ord('S'):
                    xh = 1
                else:
                    xh = 0    
                x = scale * (256 * xh + block[start + 2])
                
                y = scale * block[start + 3]
                width = scale * block[start + 4]
                height = scale * block[start + 5]
                print(sig, x, y, width, height)
                
                #get color fron signature
                if sig == 1:
                    sig_color = 'green'
                elif sig == 2:
                    sig_color = 'red'
                elif sig == 3:
                    sig_color = 'yellow'
                elif sig == 4:
                    sig_color = 'blue'
                else:
                    sig_color = 'white' #unrecognized signature                
         
                #draw rectangles
                rectangle_1 = canvas_1.create_rectangle(x, y, x + width, y + height, fill = sig_color)
                
                #center point of rectangles
                xc = x + width / 2
                yc = y + height / 2
                center = canvas_1.create_oval(xc - 1, yc - 1, xc + 1, yc + 1)

    # UPDATE CANVAS
    if blocks > 0:
        window.update()
        time.sleep(1/fps)
