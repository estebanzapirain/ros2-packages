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
from pwm_interface.srv import SetSpeedsT

#Frames per second
fps = 10

#Tolerance for angles (degrees)
ANGLE_TOLERANCE = 20

#Tolerance for distance (pixels)
MIN_DISTANCE = 30

#Velocidad de giro
TURN_SPEED = 100

#Velocidad de avance
TRAVEL_SPEED = 120

#Duración del pulso de giro
TURN_MS = 8
TRAVEL_MS = 100

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
        self.cli = self.create_client(SetSpeedsT, 'set_speeds')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('robot not available, waiting again...')
        self.req = SetSpeedsT.Request()

    def send_request(self, id, left, right, time):
        self.req.id = id
        self.req.left = left
        self.req.right = right
        self.req.time = time
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
    
    #retornar la diferencia entre ángulos. entre -180 (giro horario) y 180 (giro antihorario). 0 significa que está dentro de la tolerancia
    def GetAngleDifference(self, goal_angle, robot_angle):
        angle_between = goal_angle - robot_angle
        if angle_between > ANGLE_TOLERANCE:
            if angle_between < 180:
                return angle_between
            else:
                return angle_between - 360
        elif angle_between < -ANGLE_TOLERANCE:
            if angle_between > -180:
                return angle_between
            else:
                return 360 + angle_between
        else:
            return 0

     
    def execute_callback(self, goal_handle):
        
        global ANGLE_TOLERANCE, TURN_SPEED, TRAVEL_SPEED
        
        #Empieza a procesar la meta
        self.get_logger().info('Executing goal...')
        feedback_msg = GoToXY.Feedback()
        
        # Indicadores de cumplimiento de la meta
        pointing_at_goal = False
        close_to_goal = False
        done = False
        
        # En pos1 está la posición del robot1
        feedback_msg.partial_x = pos1.x 
        feedback_msg.partial_y = pos1.y
        feedback_msg.partial_angle = pos1.angle        

        #calcular la direccion a la que se tiene que mover direccion = arctan((goal_y-y)/(goal_x-x))
        dx = goal_handle.request.goal_x - pos1.x
        dy = goal_handle.request.goal_y - pos1.y
                    
        goal_angle = self.getAngle(dx, dy)
       
        while close_to_goal == False:
            
            angle_difference = self.GetAngleDifference(goal_angle, pos1.angle)
            
            pointing_at_goal =  angle_difference == 0
                
        # 1- girar hasta que el angulo coincida con la direccion
            
            while pointing_at_goal == False and close_to_goal == False:
               
                #self.get_logger().info('Girando...')
                # giro antihorario
                if angle_difference > 0:
                    response = self.set_speeds_client.send_request(2, TURN_SPEED , -TURN_SPEED - 20, TURN_MS) #id, vel_izq, vel_der, tiempo
                # giro horario    
                elif angle_difference < 0:
                    response = self.set_speeds_client.send_request(2, -TURN_SPEED - 20, TURN_SPEED, TURN_MS) #id, vel_izq, vel_der, tiempo
                # no girar
                else:
                    response = self.set_speeds_client.send_request(2, 0, 0, 0) #id, vel_izq, vel_der, tiempo
                    
                #Actualizar ángulo
                dx = goal_handle.request.goal_x - pos1.x
                dy = goal_handle.request.goal_y - pos1.y
                    
                goal_angle = self.getAngle(dx, dy)
                angle_difference = self.GetAngleDifference(goal_angle, pos1.angle)

                #Publicar ángulo
                feedback_msg.partial_angle = angle_difference
                #self.get_logger().info('Robot Angle: {0}'.format(pos1.angle))
                #self.get_logger().info('Goal Angle: {0}'.format(goal_angle))
                #self.get_logger().info('Angle Difference: {0}'.format(feedback_msg.partial_angle))
                #goal_handle.publish_feedback(feedback_msg)
                
                #Chequear si está apuntando en la dirección correcta
                pointing_at_goal =  angle_difference == 0
                
                #Chequear si esta cerca de la meta
                distance_to_goal = ((goal_handle.request.goal_x - pos1.x)**2 + (goal_handle.request.goal_x - pos1.y)**2)**0.5
                close_to_goal = distance_to_goal < MIN_DISTANCE
                
                
                #Hacer un ajuste más fino
                #if pointing_at_goal & (ANGLE_TOLERANCE > 5):
                #    TURN_SPEED = TURN_SPEED - 5
                #    ANGLE_TOLERANCE = ANGLE_TOLERANCE / 2
                #    pointing_at_goal = False         
                
                #Esperar durante el tiempo de actualización, restándole el tiempo del pulso
                #time.sleep(1/fps - TURN_PULSE_MS/1000)
            
            time.sleep(1/fps) 

            # 2- mover en linea recta hasta que la distancia sea 0 (o cerca)            
            self.get_logger().info('Avanzando...')
            
            distance_to_goal = ((goal_handle.request.goal_x - pos1.x)**2 + (goal_handle.request.goal_x - pos1.y)**2)**0.5
            close_to_goal = distance_to_goal < MIN_DISTANCE
            if ( not close_to_goal):
                response = self.set_speeds_client.send_request(2, TRAVEL_SPEED , TRAVEL_SPEED, TRAVEL_MS) #id, vel_izq, vel_der, tiempo

            self.get_logger().info('Distance: {0}'.format(distance_to_goal))
            time.sleep(1/fps) 

            #Publicar distancia
            #feedback_msg.partial_x = pos1.x
            #self.get_logger().info('Distance X: {0}'.format(pos1.x - goal_handle.request.goal_x))
            #self.get_logger().info('Distance Y: {0}'.format(pos1.y - goal_handle.request.goal_y))
            #goal_handle.publish_feedback(feedback_msg)

                     
        self.get_logger().info('Meta cumplida!')
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
        result.final_x = pos1.x
        result.final_y = pos1.y
        #result.final_angle = feedback_msg.partial_angle
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
    
    rate = robot_pos_subscriber.create_rate(fps)
    
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
