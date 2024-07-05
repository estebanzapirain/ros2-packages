#------------    Nodo dashboard_updater    ------------
#Envía las posiciones de los robots a la dashboard mediante MQTT, topic /Posiciones/.
#Sólo cuando no hay una meta pendiente, lo toma del topic goal.
#subscriber de goal
#subscriber de robot_pos
#publisher MQTT de /Posiciones/


#ALGORITMO
#if goal_pending = False:
#    Toma los datos del topic robot_positions
#    Envía los datos a la interfaz de Walter


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
import paho.mqtt.client as mqtt_client

# ROS message interfaces
from robot_pos_interface.msg import RobotPosition
from map_interface.msg import Goal #goal publisher

#Configuración MQTT
server="localhost"
port = 1883
ClientID = f'raspberry-pub-{time.time_ns()}'
user = ""
password = ""
topic = "/Posiciones/"
client = mqtt_client.Client(ClientID)
msg = b'{"msg":"hello"}'

# Variables de velocidad de actualización
fps = 1	#Frames per second
interval = 5 # intervalo de actualización en segundos
interval_cnt = 0 #contador para el intervalo de actualización

# Receiver address
rcv_addr = '8'

# Variables
pos1 = RobotPosition() #robot 1 position: frame, robot_id, x, y, angle
goal_pending = False       #informa si hay una meta pendiente

#vector de strings para la comunicación
#cada string es un mensaje, correspondiente a un objeto
lines_to_send = []

#Conexión MQTT
def MQTTconnect():
    print('Connected to MQTT Broker "%s"' % (server))
#     client = mqtt_client.Client(ClientID)
    client.connect(server, port)
    #client = MQTTClient(ClientID, server, 1884, user, password)
    #client.connect()
    return client

#Reconexión MQTT
def MQTTreconnect():
    print('Failed to connect to MQTT broker, Reconnecting...' % (server))
    time.sleep(5)
    client.MQTTreconnect()
    
#Limpiar el frame después de haber enviado los datos
def clear_frame(frame):
    frame.clear()
    return

#Enviar frame por MQTT al topic /Posiciones/
def send_frame(self, frame):
    global client
    for line in frame:
        self.get_logger().info(line.encode())
        time.sleep(0.05)
        client.publish(topic, line, qos=0)
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
        global pos1, goal_pending, rcv_addr, interval_cnt, interval, lines_to_send, client
        
        interval_cnt = interval_cnt + 1 #incremento el contador de intervalo
        #self.get_logger().info(str(interval_cnt))
        if interval_cnt > interval: #si hay que actualizar
            interval_cnt = 0 #reinicia el contador
           
           # DEBUG
            self.get_logger().info('Goal Pending: {0}'.format(goal_pending))
           
            #si no hay metas pendientes, envía periódicamente los datos del robot
            if not(goal_pending):
                new_line = "ID0" + rcv_addr + "R0" + str(msg.robot_id) + str(msg.x).zfill(3) + str(msg.y).zfill(3) + str(msg.angle).zfill(3)
     
                end_msg = "ID0" + rcv_addr + "F"
                
                lines_to_send.append(new_line)
                lines_to_send.append(end_msg)
                
                send_frame(self, lines_to_send)
        return

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
        return
    
    def listener_callback(self, msg):
        
        global goal_pending #refers to global variables
        print(msg)
        goal_pending = msg.goal_pending
        return

#----------------------MAIN-------------------------
def main(args=None):

    rclpy.init(args=args)
    
    #Definicion de los nodos
    robot_pos_subscriber = RobotPosSubscriber()
    goal_subscriber = GoalSubscriber()
    
    #Ejecución multi-nodo
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(robot_pos_subscriber)
    executor.add_node(goal_subscriber)
    
    # Spin in a separate thread
    executor_thread = threading.Thread(target=executor.spin, daemon=True)
    executor_thread.start()
    
    rate = robot_pos_subscriber.create_rate(fps)
    rate = goal_subscriber.create_rate(fps)

    #Conexión MQTT
    try:
        client = MQTTconnect()
    except OSError as e:
        MQTTreconnect()
    
    try:
        while rclpy.ok():
            rate.sleep()
    except KeyboardInterrupt:
        pass
    
if __name__ == '__main__':
    main()

