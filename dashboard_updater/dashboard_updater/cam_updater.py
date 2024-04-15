#!/usr/bin/env python3

# ROS standard libraries
import rclpy
from rclpy.node import Node

# Python libraries
import time
import numpy as np
import threading
import sys
import csv
from datetime import datetime

# ROS message interfaces
from robot_pos_interface.msg import RobotPosition

# Variables de velocidad de actualización
fps = 1	#Frames per second
interval = 20 # intervalo de actualización en segundos
interval_cnt = 0 #contador para el intervalo de actualización


# Receiver address
rcv_addr = '8'

# Arduino serial init
import serial
arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
arduino.reset_input_buffer()

# Variables
pos1 = RobotPosition() #robot 1 position: frame, robot_id, x, y, angle
new_data = False       #informa si hay nuevos datos de posición

#vector de strings para la comunicación
#cada string es un mensaje, correspondiente a un objeto
lines_to_send = []

def clear_frame(frame):
    return

def send_frame(frame):
    for line in frame:
        arduino.write(line.encode())
    clear_frame(frame)
    return

# ROBOT POS SUBSCRIBER
class RobotPosSubscriber(Node):

    def __init__(self):
        super().__init__('robot_pos_subscriber')
        self.subscription = self.create_subscription(
            RobotPosition,
            'robot_pos',
            self.listener_callback,
            1)
        self.subscription  # prevent unused variable warning
        #self.get_logger().info("RobotPosSubscriber")
        return
    
    def listener_callback(self, msg):
        #global variables
        global pos1, new_data, rcv_addr, interval_cnt, interval, lines_to_send
        
        interval_cnt = interval_cnt + 1 #incremento el contador de intervalo
        #self.get_logger().info(str(interval_cnt))
        if interval_cnt > interval: #si hay que actualizar
            interval_cnt = 0 #reinicia el contador
       
            #guarda los datos del robot
            new_line = "ID0" + rcv_addr + "R0" + str(msg.robot_id) + str(msg.x).zfill(3) + str(msg.y).zfill(3) + str(msg.angle).zfill(3)
 
            self.get_logger().info(new_line)
            lines_to_send = new_line
            send_frame(lines_to_send)
        return
    
def main(args=None):

    rclpy.init(args=args)
    
    #Definicion de los nodos
    robot_pos_subscriber = RobotPosSubscriber()

    
    #Ejecución multi-nodo
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(robot_pos_subscriber)
   
    # Spin in a separate thread
    executor_thread = threading.Thread(target=executor.spin, daemon=True)
    executor_thread.start()
    
    rate = robot_pos_subscriber.create_rate(fps)
    
    try:
        while rclpy.ok():
            rate.sleep()
    except KeyboardInterrupt:
        pass
    
if __name__ == '__main__':
    main()

