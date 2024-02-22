############################################################
#
# pixy_map_getter.py
# 
# ROS Package: map_updater
# Node type: publisher to topic "map"

# Objective: get map of signatures from PixyCam

# Connects to Arduino, which is connected to Pixy Cam
# Sends command 'c', gets data from detected blocks
# data format: "sig: 1 x: 5 y: 117 width: 10 height: 23"
#
############################################################



import rclpy
from rclpy.node import Node

# Custom Block message format
# Message format: "sig: 1 x: 5 y: 117 width: 10 height: 23"
from map_interface.msg import Block


# Arduino serial init
import serial
arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
arduino.reset_input_buffer()

#Data length, used to check if data is valid
BLOCK_LENGTH = 6
BLOCKS_EXPECTED = 4

#Minimum block size to assume data is valid
MIN_SIZE = 50

#frame number
frame = 0

#frames per second
fps = 2

class Publisher(Node):

    def __init__(self):
        super().__init__('map_publisher')
        self.publisher_ = self.create_publisher(Block, 'map', 10) # (message, topic, queue_size)
        timer_period = 1/fps  

        self.timer = self.create_timer(timer_period, self.timer_callback)



    def timer_callback(self):
        global frame
        
        msg = Block()

        data = [] # init empty data structure
    
        arduino.write(b'ID01m\r\n') # send command "m" (GET_MAP) trough serial port
    
        blocks = 0
    
        # READ DATA
        while arduino.in_waiting>0: # while there's data available
            str = arduino.readline().rstrip() # read incoming line and throw away ending \r\n
            data.append(str) # add line to existing data
            blocks += 1

        print(blocks) # print quantity of blocks
        
        if blocks >= BLOCKS_EXPECTED:  # if data is valid
            frame += 1
            
       # PROCESS DATA    
        for block in data: #for each block
            if (len(block)>0): #if there is data
      
                if block[0] == 73: #if begins with IDxx, data starts at index 4
                    start = 4
                else:
                    start = 0
                    
                if len(block)>=start + BLOCK_LENGTH: #check length of data    
                                        
                    #--------------    split block       -----------------------
                    msg.frame = frame
                    msg.sig = block[start]
                    
                    #x range exceeds 8 bits, so it comes divided into 2 bytes
                    #MSB is 'S' if x exceeds 256
                    if block[start + 1] == ord('S'):
                        xh = 1
                    else:
                        xh = 0    
                    msg.x = 256 * xh + block[start + 2]
                    
                    msg.y = block[start + 3]
                    msg.width = block[start + 4]
                    msg.height = block[start + 5]
                    #-----------------------------------------------------------
                    
                    #Publish
                    #print(msg.frame, msg.sig, msg.x, msg.y, msg.width, msg.height)
                    if (msg.width>MIN_SIZE) & (msg.height>MIN_SIZE): 
                        self.publisher_.publish(msg)
                    # self.get_logger().info('Block: "%s"' % block)


def main(args=None):

    rclpy.init(args=args)

    map_publisher = Publisher()

    rclpy.spin(map_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    map_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
