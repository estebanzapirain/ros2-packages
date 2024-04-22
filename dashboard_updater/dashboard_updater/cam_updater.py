#------------    Nodo dashboard_updater    ------------
# Es subscriber de robot_positions, client de action gotoxy

#ALGORITMO
#if goal_pending = False:
#    Toma los datos del topic robot_positions
#    Envía los datos a la interfaz de Walter
#Si recibe una meta:
#    goal_pending = True
#    Envía la meta al robot
#    Espera que se cumpla
#    goal_pending = False


#!/usr/bin/env python3

# ROS standard libraries
import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

# Python libraries
import time
import numpy as np
import threading
import sys
import csv
from datetime import datetime

# ROS message interfaces
from robot_pos_interface.msg import RobotPosition
from gotoxy_interface.action import GoToXY #Gotoxy client
from map_interface.msg import Goal #goal publisher

# Variables de velocidad de actualización
fps = 1	#Frames per second
interval = 5 # intervalo de actualización en segundos
interval_cnt = 0 #contador para el intervalo de actualización


# Receiver address
rcv_addr = '8'

# Arduino serial init
import serial
arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
arduino.reset_input_buffer()

# Variables
pos1 = RobotPosition() #robot 1 position: frame, robot_id, x, y, angle
goal_pending = False       #informa si hay una meta pendiente

#vector de strings para la comunicación
#cada string es un mensaje, correspondiente a un objeto
lines_to_send = []

#Limpiar el frame después de haber enviado los datos
def clear_frame(frame):
    frame.clear()
    return

def send_frame(self, frame):
    for line in frame:
        arduino.write(line.encode())
        self.get_logger().info(line.encode())
        time.sleep(0.05)

#Fin de datos del frame
#     end_msg = "ID0" + rcv_addr + "F"
#     arduino.write(end_msg.encode())
#     self.get_logger().info(end_msg)
    
    
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
        global pos1, goal_pending, rcv_addr, interval_cnt, interval, lines_to_send
        
        interval_cnt = interval_cnt + 1 #incremento el contador de intervalo
        #self.get_logger().info(str(interval_cnt))
        if interval_cnt > interval: #si hay que actualizar
            interval_cnt = 0 #reinicia el contador
       
            #si no hay metas pendientes, envía periódicamente los datos del robot
            if not(goal_pending):
                new_line = "ID0" + rcv_addr + "R0" + str(msg.robot_id) + str(msg.x).zfill(3) + str(msg.y).zfill(3) + str(msg.angle).zfill(3)
     
                end_msg = "ID0" + rcv_addr + "F"
                
                lines_to_send.append(new_line)
                lines_to_send.append(end_msg)
                
                send_frame(self, lines_to_send)
        return

#Procesar meta
class GoToXYClient(Node):

    def __init__(self):
        super().__init__('gotoxy_client')
        self._action_client = ActionClient(self, GoToXY, 'gotoxy')

    def send_goal(self, x, y, angle):
        goal_msg = GoToXY.Goal()
        goal_msg.goal_x = x
        goal_msg.goal_y = y
        goal_msg.goal_angle = angle

        self._action_client.wait_for_server()

        self._send_goal_future = self._action_client.send_goal_async(
            goal_msg,
            feedback_callback=self.feedback_callback)

        self._send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()

        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return

        self.get_logger().info('Goal accepted :)')

        self._get_result_future = goal_handle.get_result_async()

        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        
        global goal_pending
        
        result = future.result().result
        self.get_logger().info('FinalX: {0}'.format(result.final_x))
        self.get_logger().info('FinalY: {0}'.format(result.final_y))
        goal_pending = False
        
        rclpy.shutdown()

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        self.get_logger().info('Received feedback: {0}'.format(feedback.partial_angle))



def get_goal():
    
    global goal_pending
    
    while arduino.in_waiting>0: # while there's data available
        str = arduino.readline().rstrip() # read incoming line and throw away ending \r\n
        origen = str[:4]
        if origen=="ID08":
            robot = str[4:6]
            x = int(str[6:9])
            y = int(str[9:12])
            alfa = int(str[12:15])
            self.get_logger().info('x={0} y={1} alfa={2}'.format(x,y,alfa))
            goal_pending = True
            action_client.send_goal(x, y, alfa)
    return


def main(args=None):

    rclpy.init(args=args)
    
    #Definicion de los nodos
    robot_pos_subscriber = RobotPosSubscriber()
    action_client = GoToXYClient()
    
    #Ejecución multi-nodo
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(robot_pos_subscriber)
    executor.add_node(action_client)
    
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

