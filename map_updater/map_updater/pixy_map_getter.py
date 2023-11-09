############################################################
#
# pixy_map_request.py
# 
# ROS Package: map_updater
# Node type: publisher to topic "map"

# Objective: get map of signatures from PixyCam

# Connects to Arduino, which is connected to Pixy Cam
# Sends command 'c', gets blocks detected
# format sig: 1 x: 5 y: 117 width: 10 height: 23
#
############################################################



import rclpy
from rclpy.node import Node

# Message format: "sig: 1 x: 5 y: 117 width: 10 height: 23"
from std_msgs.msg import String

import serial

arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
arduino.reset_input_buffer()

class Publisher(Node):

    def __init__(self):
        super().__init__('map_publisher')
        self.publisher_ = self.create_publisher(String, 'map', 10) # (message, topic, queue_size)
        timer_period = 0.5  # seconds

        self.timer = self.create_timer(timer_period, self.timer_callback)



    def timer_callback(self):
        msg = String()
        arduino.write(b'm\r')
        valor = arduino.readline().decode('ascii').rstrip()
        if valor != b'':
                msg.data = valor
                self.publisher_.publish(msg)
                self.get_logger().info('Bloque: "%s"' % msg.data)


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
