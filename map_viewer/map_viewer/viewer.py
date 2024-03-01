import rclpy
from rclpy.node import Node

from map_interface.msg import Block
import tkinter as tk

# Create the main window
window = tk.Tk()
window.geometry("640x480")
window.title("PixyCam SPI Viewer")
# window['background'] = 'black'

# Dimensions
w = 640
h = 480
scale = w / 320 #Scale factor relative to 320x240
frame = 0

#Máximo desfasaje en frames para considerar que los objetos son de un mismo frame
MAX_FRAME_DELAY = 2

#Si la caja de la cámara está invertida con respecto al punto de vista
INV_CAMERA = False

# Create a Canvas widget
canvas_1 = tk.Canvas(window, width=w, height=h)
canvas_1.pack()

class MapSubscriber(Node):

    def __init__(self):
        super().__init__('map_subscriber')
        self.subscription = self.create_subscription(
            Block,
            'map',
            self.listener_callback,
            50)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        global frame
        if abs(msg.frame - frame) > MAX_FRAME_DELAY:
            canvas_1.delete('all') #clear canvas
            frame = msg.frame

        #get color fron signature
        if msg.sig == 1:
            sig_color = 'green'
        elif msg.sig == 2:
            sig_color = 'red'
        elif msg.sig == 3:
            sig_color = 'yellow'
        elif msg.sig == 4:
            sig_color = 'blue'
        else:
            sig_color = 'white' #unrecognized signature                
 

        #draw rectangles
        rectangle_x = scale * msg.x
        rectangle_y = scale * msg.y
        if INV_CAMERA:
            rectangle_x = w - rectangle_x
            rectangle_y = h - rectangle_y
        
        rectangle_1 = canvas_1.create_rectangle(rectangle_x, rectangle_y, rectangle_x + scale * msg.width, rectangle_y + scale * msg.height, fill = sig_color)
        
        #center point of rectangles
        
        xc = rectangle_x + scale * msg.width / 2
        yc = rectangle_y + scale * msg.height / 2
#        if INV_CAMERA:
#            xc = w - xc
#            yc = h - yc
                
        center = canvas_1.create_oval(xc - 1, yc - 1, xc + 1, yc + 1)
        #labels
        widget = tk.Label(canvas_1, text='(0,0)', fg='black')
        widget.pack()
        canvas_1.create_window(0, 0, window=widget)
      
    # UPDATE CANVAS
        window.update()

def main(args=None):

    
    rclpy.init(args=args)

    map_subscriber = MapSubscriber()

    rclpy.spin(map_subscriber)
    
    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    map_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
