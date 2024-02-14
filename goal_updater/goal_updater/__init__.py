############################################################
#
# ROS Package: goal_updater
# Node type: subscriber to topic "goal", publisher to topic "map"

# Objective: publish goals to map, so they can be visible in map_viewer

############################################################


#Import libraries
import rclpy
from rclpy.node import Node
import threading

# Custom Block message format
from map_interface.msg import Block, Goal

#frames per second
fps = 10

#size of goal dot (pixels)
dot_size = 5

#Init variables
new_goal = Goal()
new_data = False

#Subscriber to topic "goal", picks up goal coordinates
class GoalSubscriber(Node):

    def __init__(self):
        super().__init__('goal_subscriber')
        self.subscription = self.create_subscription(
            Goal,
            'goal',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        
        global new_goal, new_data #refers to global variables
        print(msg)
        new_data = True
        new_goal = msg
            
#Publisher to topic "map", informs (x,y) and angle of new goals.
class Publisher(Node):

    def __init__(self):
        super().__init__('map_publisher')
 
        self.publisher_ = self.create_publisher(Block, 'map', 10) # (message, topic, queue_size)
 
        timer_period = 1/fps
        print(timer_period)
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        global new_goal, new_data
        
        #Init new message (block format)
        msg = Block()
        
        #if GoalSubscriber gets new data from a goal
        if new_data:
            #data is not new
            new_data = False
            msg.sig = 3
            msg.x = new_goal.x
            msg.y = new_goal.y
            msg.width = dot_size
            msg.height = dot_size
            msg.frame = 0
            
   #Publish
            #print(msg.robot_id, msg.frame, msg.x, msg.y, msg.angle)
            self.publisher_.publish(msg)
            #self.get_logger().info('Goal: "%s"' % msg)


def main(args=None):

    rclpy.init(args=args)

    #Start nodes 
    goal_subscriber = GoalSubscriber()
    #rclpy.spin(map_subscriber)
    
    map_publisher = Publisher()
    #rclpy.spin(robot_pos_publisher)
    
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(goal_subscriber)
    executor.add_node(map_publisher)
    # Spin in a separate thread
    executor_thread = threading.Thread(target=executor.spin, daemon=True)
    executor_thread.start()
    
    rate = goal_subscriber.create_rate(fps)
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
