#!/usr/bin/env python3

#ROS standard libraries
import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node

#Python libraries
import time
import numpy as np
import threading
import sys

#ROS message interfaces
from robot_pos_interface.msg import RobotPosition
from gotoxy_interface.action import GoToXY
from pwm_interface.srv import SetSpeeds

#Frames per second
fps = 2

#Tolerance for angles (degrees)
ANGLE_TOLERANCE = 20

#Tolerance for distance (pixels)
MIN_DISTANCE = 20

#Velocidad de giro
TURN_SPEED = 80

#Duración del pulso de giro
TURN_PULSE_MS = 300

#Conversión de radianes a grados
RAD2GRAD = 180/np.pi

#Punto medio
XM = 160
YM = 120

#Variables
pos1 = RobotPosition() #robot 1 position: frame, robot_id, x, y, angle

#ROBOT POS SUBSCRIBER
class RobotPosSubscriber(Node):

    def __init__(self):
        super().__init__('robot_pos_subscriber')
        self.subscription = self.create_subscription(
            RobotPosition,
            'robot_pos',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        #global variables
        global pos1
        
        #Guardo los datos del robot
        if msg.robot_id == 1:
            pos1 = msg

            
# SET SPEEDS CLIENT
class SetSpeedsClient(Node):

    def __init__(self):
        super().__init__('set_speeds_client')
        self.cli = self.create_client(SetSpeeds, 'set_speeds')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('robot not available, waiting again...')
        self.req = SetSpeeds.Request()

    def send_request(self, id, left, right):
        self.req.id = id
        self.req.left = left
        self.req.right = right
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()
    
# GOTOXY ACTION SERVER
class GoToXYActionServer(Node):

    def __init__(self):
        super().__init__('gotoxy_action_server')
        self._action_server = ActionServer(
            self,
            GoToXY,
            'gotoxy',
            self.execute_callback)
        self.set_speeds_client = SetSpeedsClient()
    
    #retorna ángulo en grados
    def getAngle(self,dx,dy):
        dy = -dy        
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
    
    def execute_callback(self, goal_handle):
        
        global ANGLE_TOLERANCE, TURN_SPEED
        
        #Empieza a procesar la meta
        self.get_logger().info('Executing goal...')
        feedback_msg = GoToXY.Feedback()
        
        # Indicadores de cumplimiento de la meta
        pointing_at_goal = False
        close_to_goal = False
        in_goal_angle = False
        
        # En pos1 está la posición del robot1
        feedback_msg.partial_x = pos1.x 
        feedback_msg.partial_y = pos1.y
        feedback_msg.partial_angle = pos1.angle        
        
        #calcular la direccion a la que se tiene que mover direccion = arctan((goal_y-y)/(goal_x-x))
        dx = goal_handle.request.goal_x - XM
        dy = goal_handle.request.goal_y - YM
                
        goal_angle = self.getAngle(dx, dy)
        angle_difference = abs(pos1.angle-goal_angle)
        pointing_at_goal =  angle_difference < ANGLE_TOLERANCE
        
        # 1- girar hasta que el angulo coincida con la direccion
        while pointing_at_goal == False:
           
            
            # VER LO DE LOS ANGULOS MAYORES O MENORES DE 180, PARA DONDE CONVIENE GIRAR
            # Si el angulo de la meta es mayor que al que está apuntando el robot, girar a la derecha (sentido antihorario)
            if goal_angle < pos1.angle:
                response = self.set_speeds_client.send_request(2, -TURN_SPEED , TURN_SPEED) #id, vel_izq, vel_der
            # Sino, girar a la izquierda    
            else:
                response = self.set_speeds_client.send_request(2, TURN_SPEED, -TURN_SPEED) #id, vel_izq, vel_der
            
            #Actualizar ángulo
            angle_difference = abs(pos1.angle - goal_angle)

            #Publicar ángulo
            feedback_msg.partial_angle = angle_difference
            self.get_logger().info('Robot Angle: {0}'.format(pos1.angle))
            self.get_logger().info('Goal Angle: {0}'.format(goal_angle))
            self.get_logger().info('Angle Difference: {0}'.format(feedback_msg.partial_angle))
            goal_handle.publish_feedback(feedback_msg)
            
            #Chequear si está apuntando en la dirección correcta
            pointing_at_goal =  angle_difference < ANGLE_TOLERANCE
            
            #Hacer un ajuste más fino
            if pointing_at_goal & (ANGLE_TOLERANCE > 5):
                TURN_SPEED = TURN_SPEED - 5
                ANGLE_TOLERANCE = ANGLE_TOLERANCE / 2
                pointing_at_goal = False         
            
            #Esperar durante el tiempo de actualización, restándole el tiempo del pulso
            #time.sleep(1/fps - TURN_PULSE_MS/1000)
            time.sleep(1/fps) 
        
        # 2- mover en linea recta hasta que la distancia sea 0 (o cerca)
        while close_to_goal == False:
           
            
            # VER LO DE LOS ANGULOS MAYORES O MENORES DE 180, PARA DONDE CONVIENE GIRAR
            # Si el angulo de la meta es mayor que al que está apuntando el robot, girar a la derecha (sentido antihorario)
            distance_to_goal = ((goal_handle.request.goal_x - pos1.x)**2 + (goal_handle.request.goal_x - pos1.y)**2)**0.5
            if ( distance_to_goal > MIN_DISTANCE):
                response = self.set_speeds_client.send_request(2, TURN_SPEED , TURN_SPEED) #id, vel_izq, vel_der
            else:
                close_to_goal = True
            
            #Publicar distancia
            feedback_msg.partial_x = pos1.x
            self.get_logger().info('Distance X: {0}'.format(pos1.x - goal_handle.request.goal_x))
            self.get_logger().info('Distance Y: {0}'.format(pos1.y - goal_handle.request.goal_y))
            goal_handle.publish_feedback(feedback_msg)

            time.sleep(1/fps)             
   
        # 3- girar el angulo hasta que coincida con el goal_angle
        
        
        
        # Acá hace todo
        # Tiene que ir moviendo los motores y reportando feedback de la distancia al objetivo
        # goal_handle.request.goal_x es la posicion destino
         
 
#         while (feedback_msg.partial_x < goal_handle.request.goal_x):
#         #Dar feedback de la posición actual del robot (o la distancia al destino)
#                 feedback_msg.partial_x = feedback_msg.partial_x + 1
#                 self.get_logger().info('Feedback: {0}'.format(feedback_msg.partial_x))
#                 goal_handle.publish_feedback(feedback_msg)
#                 time.sleep(1/fps)

        goal_handle.succeed()

        result = GoToXY.Result()
#        result.final_id = feedback_msg.partial_id
        result.final_x = feedback_msg.partial_x
        result.final_y = feedback_msg.partial_y
        result.final_angle = feedback_msg.partial_angle
        return result


def main(args=None):
    

    rclpy.init(args=args)
    
    #Definicion de los nodos
    gotoxy_action_server = GoToXYActionServer()
    robot_pos_subscriber = RobotPosSubscriber()
#     set_speeds_client = SetSpeedsClient()
    
    #Ejecución multi-nodo
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(gotoxy_action_server)
    executor.add_node(robot_pos_subscriber)
    #executor.add_node(set_speeds_client)    
   
    # Spin in a separate thread
    executor_thread = threading.Thread(target=executor.spin, daemon=True)
    executor_thread.start()
    
    rate = robot_pos_subscriber.create_rate(2)
    
    try:
        while rclpy.ok():
            #print('Help me body, you are my only hope')
            rate.sleep()
    except KeyboardInterrupt:
        pass
    
#     try:
#         rclpy.spin(gotoxy_action_server)
#     except KeyboardInterrupt:
#         pass


if __name__ == '__main__':
    main()
