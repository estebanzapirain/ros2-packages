############################################################
#
# ROS Package: robot_positions
# Node type: subscriber to topic "map", publisher to topic "robot_pos"

# Objective: publish robot positions: (x,y) and angle they are facing

# Gets blocks from a frame, extracts pairs of signatures  corresponding to robots,
# and calculates its id, center coordinates and angle
############################################################


#Import libraries
import rclpy
from rclpy.node import Node
import numpy as np
import threading

# Custom Block message format
# Message format: "frame: 212sig: 1 x: 5 y: 117 width: 10 height: 23"
from map_interface.msg import Block
from robot_pos_interface.msg import RobotPosition

#Conversión de radianes a grados
RAD2GRAD = 180/np.pi

#frames per second
fps = 2

#Init variables
msg1 = Block()
msg2 = Block()
new_data = False

#Subscriber to topic "map", picks up data from robots
class MapSubscriber(Node):

    def __init__(self):
        super().__init__('robot_pos_subscriber')
        self.subscription = self.create_subscription(
            Block,
            'map',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        
        global msg1, msg2, new_data #refers to global variables
        
        #msg1 = front msg2=back
        if (msg.sig == 1):
            msg1 = msg
        elif (msg.sig == 2):
            msg2 = msg
        
        #if both msg1 and msg2 belong to same frame, we got new data and enable publishing
        if (msg1.frame == msg2.frame):
            new_data = True
            
#Publisher to topic "robot_pos", informs (x,y) and angle of robots in each frame
class Publisher(Node):

    def __init__(self):
        super().__init__('robot_pos_publisher')
 
        self.publisher_ = self.create_publisher(RobotPosition, 'robot_pos', 10) # (message, topic, queue_size)
 
        timer_period = 1/fps
        print(timer_period)
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def getCenter(self,x1,y1,x2,y2):
        xc = int((x1 + x2)/2)
        yc = int((y1 + y2)/2)
        return xc,yc

    #retorna ángulo en grados
    def getAngle(self,dx,dy):
        dx = -dx
        if (dx!=0):
            angle = np.arctan(dy/dx) * RAD2GRAD
        elif (dy<0):
            angle = 270
        else:
            angle = 90

        if (dx<0): #segundo/tercer cuadrante
            angle = angle + 180
        elif (dx>0) & (dy<0): #cuarto cuadrante
            angle = angle + 360
        elif (dy == 0):
            if dx>0:
                angle = 0
            else:
                angle = 180
        return int(angle)

    def timer_callback(self):
        global msg1, msg2, new_data
        
        #Init new mesagge
        msg = RobotPosition()
        #if MapSubscriber got new data from a robot
        if new_data:
            #data is not new
            new_data = False
            
            #position = center from both signatures
            msg.x, msg.y = self.getCenter(msg1.x, msg1.y, msg2.x, msg2.y)
            
            #get angle from coordinates
            dx = msg2.x - msg1.x
            dy = msg2.y - msg1.y
            msg.angle = self.getAngle(dx, dy)
            self.get_logger().info('dx: {0}'.format(dx))
            self.get_logger().info('dy: {0}'.format(dy))
            self.get_logger().info('angle: {0}'.format(msg.angle))
            msg.robot_id = 1
            msg.frame = msg1.frame
		    
	    #Publish
	    #print(msg.robot_id, msg.frame, msg.x, msg.y, msg.angle)
            self.publisher_.publish(msg)
	
            self.get_logger().info('Robot: "%s"' % msg)


def main(args=None):

    rclpy.init(args=args)

    #Start nodes 
    map_subscriber = MapSubscriber()
    #rclpy.spin(map_subscriber)
    
    robot_pos_publisher = Publisher()
    #rclpy.spin(robot_pos_publisher)
    
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(map_subscriber)
    executor.add_node(robot_pos_publisher)
    # Spin in a separate thread
    executor_thread = threading.Thread(target=executor.spin, daemon=True)
    executor_thread.start()
    
    rate = map_subscriber.create_rate(2)
    try:
        while rclpy.ok():
            #print('Help me body, you are my only hope')
            rate.sleep()
    except KeyboardInterrupt:
        pass

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
#     map_subscriber.destroy_node()
#     robot_pos_publisher.destroy_node()
#     rclpy.shutdown()


if __name__ == '__main__':
    main()
