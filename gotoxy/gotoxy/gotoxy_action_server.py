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
import csv
from datetime import datetime

#ROS message interfaces
from robot_pos_interface.msg import RobotPosition
from gotoxy_interface.action import GoToXY
from pwm_interface.srv import SetSpeedsT

#Frames per second
fps = 10

#Tolerance for angles (degrees)
ANGLE_TOLERANCE = 20

#Tolerance for distance (pixels)
MIN_DISTANCE = 10
NEAR_GOAL = 60
NEAR_WALL = 20

#Velocidad de giro
TURN_SPEED = 120

#Velocidad de avance
TRAVEL_SPEED = 120
REVERSE_SPEED = -120

#Duración del pulso de giro
TURN_MS = 50


#Conversión de radianes a grados
RAD2GRAD = 180/np.pi

#Medidas de la imagen
IMAGE_W = 320
IMAGE_H = 240

#Punto medio
XM = IMAGE_W // 2
YM = IMAGE_H // 2

#Variables
pos1 = RobotPosition() #robot 1 position: frame, robot_id, x, y, angle
new_data = False       #informa si hay nuevos datos de posición

#Variables para estadistica
st_steps = 0              #cantidad de pasos para el cumplimiento de una meta
st_initial_distance = 0   #distancia entre la meta y la posición inicial 
st_time = 0               #tiempo de procesamiento 
#distancia recorrida
st_distance = {
    "x": 0,
    "y": 0    
    }
first_pos = True
prev_x = 0
prev_y = 0

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
        global pos1, new_data
        
        #Guardo los datos del robot
        if msg.robot_id == 1:
            pos1 = msg
            new_data = True
            #self.get_logger().info('New data')
            

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
    
    # retornar la diferencia entre ángulos. entre -180 (giro horario) y 180 (giro antihorario). 0 significa que está dentro de la tolerancia
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
    
    # diferencia en grados entre el robot y la meta
    def UpdateAngleDifference(self, goal_handle, pos):
        dx = goal_handle.request.goal_x - pos.x
        dy = goal_handle.request.goal_y - pos.y
        goal_angle = self.getAngle(dx, dy)
        return self.GetAngleDifference(goal_angle, pos.angle)

    # decidir el sentido de giro
    def Turn(self, angle_difference, TURN_SPEED, TURN_MS):
        # giro antihorario
        if angle_difference > 0:
            response = self.set_speeds_client.send_request(2, TURN_SPEED , -TURN_SPEED, TURN_MS) #id, vel_izq, vel_der, tiempo
        # giro horario    
        elif angle_difference < 0:
            response = self.set_speeds_client.send_request(2, -TURN_SPEED, TURN_SPEED, TURN_MS) #id, vel_izq, vel_der, tiempo
        # no girar
        else:
            response = self.set_speeds_client.send_request(2, 0, 0, 0) #id, vel_izq, vel_der, tiempo
        return 0
    
    # calculo de la distancia a la meta
    def CalcDistance(self, goal_handle, pos):
        distance = ((goal_handle.request.goal_x - pos.x)**2 + (goal_handle.request.goal_y - pos.y)**2)**0.5
        return distance
    
    # chequear si el robot está cerca de un borde    
    def IsNearWall(self, pos, NEAR_WALL, IMAGE_W, IMAGE_H):
        near_west = (pos.x < NEAR_WALL) and (pos.angle>=135 and pos.angle<225)
        near_east = (pos.x > IMAGE_W - NEAR_WALL) and (pos.angle<45 or pos.angle>=315)
        near_south = (pos.y < NEAR_WALL) and (pos.angle>=225 or pos.angle<315)
        near_north = (pos.y > IMAGE_H - NEAR_WALL) and (pos.angle>=45 and pos.angle<135)
        return near_west or near_east or near_north or near_south
    
    # actualizar el mensaje de feedback
    def update_feedback(self, feedback_msg, goal_handle, pos):
        feedback_msg.robot_x = pos1.x
        feedback_msg.robot_y = pos1.y
        feedback_msg.robot_angle = pos1.angle
        feedback_msg.distance_to_goal = int(self.CalcDistance(goal_handle, pos1))
        feedback_msg.angle_difference = self.UpdateAngleDifference(goal_handle, pos1)
        self.get_logger().info('Feedback: {0}'.format(feedback_msg))
    
    # actualizar el log
    def update_log(self, filename, feedback_msg, state, pos):
        global first_pos, prev_x, prev_y, st_distance
        with open(filename,'a') as fd:
            csvwriter = csv.writer(fd, delimiter ='|')
            data = [feedback_msg.robot_x, feedback_msg.robot_y, feedback_msg.distance_to_goal, feedback_msg.robot_angle, feedback_msg.angle_difference, state]
            csvwriter.writerow(data)
        #estadisticas
        if first_pos:
            first_pos = False
            prev_x = pos1.x
            prev_y = pos1.y
        else:
            st_distance["x"] += abs(pos.x - prev_x)
            st_distance["y"] += abs(pos.y - prev_y)
    
    # función principal de procesamiento de meta
    def execute_callback(self, goal_handle):
        
        global ANGLE_TOLERANCE, TURN_SPEED, TRAVEL_SPEED, REVERSE_SPEED, TURN_MS, new_data, st_distance
        
        #Empieza a procesar la meta
        self.get_logger().info('Executing goal...')
        
        #Iniciar archivo de feedback
        filename = "src/redros_logs/goal_logger" + str(datetime.now()) + ".csv"
        
        with open(filename, 'w') as csvfile:
            csvwriter = csv.writer(csvfile, delimiter ='|')
             # el encabezado del archivo son los datos de la meta
            fields = ['goal_x', 'goal_y', 'goal_angle','robot_id','','']
            data = [goal_handle.request.goal_x, goal_handle.request.goal_y, goal_handle.request.goal_angle, '1','','']
            csvwriter.writerow(fields)
            csvwriter.writerow(data)
            
            # encabezados de columna de datos
            fields = ['robot_x', 'robot_y', 'distance_to_goal', 'robot_angle', 'angle_difference', 'step']
            csvwriter.writerow(fields)
            
        #Feedback inicial
        feedback_msg = GoToXY.Feedback() #inicializacion
        
        #datos iniciales
        self.update_feedback(feedback_msg, goal_handle, pos1) 
        self.update_log(filename, feedback_msg, '1', pos1)
        
        # estadisticas
        st_initial_distance = feedback_msg.distance_to_goal
        st_steps = 0
        st_time = time.time()
        st_distance["x"] = 0
        
        # Indicadores de cumplimiento de la meta
        pointing_at_goal = False
        close_to_goal = False
        done = False
        TRAVEL_MS = 120 # velocidad inicial de avance
        
        while close_to_goal == False:
            angle_difference = self.UpdateAngleDifference(goal_handle, pos1)
            pointing_at_goal = angle_difference == 0
                        
        # 1- girar hasta que el angulo coincida con la direccion
            
            while pointing_at_goal == False and close_to_goal == False:
               
                if new_data:
                    new_data = False
                    self.get_logger().info('Girando...')
                    
                    # estadisticas
                    st_steps += 1
                    
                    # Girar de acuerdo al ángulo
                    self.Turn(angle_difference, TURN_SPEED, TURN_MS)
                    
                    # Chequear si no está contra una pared
                    if self.IsNearWall(pos1, NEAR_WALL, IMAGE_W, IMAGE_H):
                        response = self.set_speeds_client.send_request(2, REVERSE_SPEED , REVERSE_SPEED, TRAVEL_MS)  
                        self.get_logger().info('De reversa: speed= {0}'.format(REVERSE_SPEED))
                    #Actualizar ángulo
                    angle_difference = self.UpdateAngleDifference(goal_handle, pos1)
                    self.get_logger().info('Angle Difference: {0}'.format(angle_difference))

                    #Chequear si está apuntando en la dirección correcta
                    pointing_at_goal = angle_difference == 0
                    
                    #Chequear si esta cerca de la meta
                    distance_to_goal = self.CalcDistance(goal_handle, pos1)
                    close_to_goal = distance_to_goal < MIN_DISTANCE
                    
                    self.update_feedback(feedback_msg, goal_handle, pos1) 
                    self.update_log( filename, feedback_msg, '1', pos1)
            
                    time.sleep(1/fps) 

        # 2- mover en linea recta hasta que la distancia sea 0 (o cerca)            
            if new_data:
                new_data = False
                self.get_logger().info('Avanzando...')
                
                # estadisticas
                st_steps += 1
                
                distance_to_goal = self.CalcDistance(goal_handle, pos1)
                close_to_goal = distance_to_goal < MIN_DISTANCE
               
                self.get_logger().info('Distance: {0}'.format(distance_to_goal))
                
                if ( not close_to_goal):
                    if distance_to_goal < NEAR_GOAL:
                        TRAVEL_MS = 60
                        TURN_MS = 30
                    response = self.set_speeds_client.send_request(2, TRAVEL_SPEED , TRAVEL_SPEED, TRAVEL_MS) #id, vel_izq, vel_der, tiempo
                    # Chequear si no está contra una pared
                    if self.IsNearWall(pos1, NEAR_WALL, IMAGE_W, IMAGE_H):
                        response = self.set_speeds_client.send_request(2, REVERSE_SPEED , REVERSE_SPEED, TRAVEL_MS)
                        self.get_logger().info('De reversa: X={0} Y={1}'.format(pos1.x, pos1.y))
                time.sleep(1/fps) 
            self.update_feedback(feedback_msg, goal_handle, pos1) 
            self.update_log(filename, feedback_msg, '2', pos1)
            
        # 3- girar el angulo hasta que coincida con el goal_angle
            goal_angle_difference = self.GetAngleDifference(goal_handle.request.goal_angle, pos1.angle)
            done = goal_angle_difference == 0
            
        while done == False:
            # estadisticas
            st_steps += 1
            
            self.Turn(goal_angle_difference, TURN_SPEED, TURN_MS)
            time.sleep(1/fps)
            goal_angle_difference = self.GetAngleDifference(goal_handle.request.goal_angle, pos1.angle)
            done = goal_angle_difference == 0       
            self.get_logger().info('Goal Angle Difference: {0}'.format(goal_angle_difference))
            
            self.update_feedback(feedback_msg, goal_handle, pos1) 
            self.update_log(filename, feedback_msg, '3', pos1)
    
        goal_handle.succeed()
        self.update_feedback(feedback_msg, goal_handle, pos1) 
        self.update_log(filename, feedback_msg, '4', pos1)

        self.get_logger().info('Meta cumplida!')

        
        # estadisticas finales
        st_time = abs(time.time() - st_time)
        self.get_logger().info('Number of steps: {0}'.format(st_steps))
        self.get_logger().info('Ellapsed time: {0} seconds'.format(st_time))
        with open(filename,'a') as fd:
            csvwriter = csv.writer(fd, delimiter ='|')
            closing_header = ['Overall statistics','','','','','']
            csvwriter.writerow(closing_header)
            closing_header = ['Initial distance','Number of steps','Ellapsed time [seconds]','Travelled x', 'Travelled y', 'Travelled distance [pixels]']
            csvwriter.writerow(closing_header)
            data = [st_initial_distance, st_steps, st_time, st_distance["x"], st_distance["y"], (st_distance["x"]**2 + st_distance["y"]**2)**0.5]
            csvwriter.writerow(data)
            
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
    
    #Ejecución multi-nodo
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(gotoxy_action_server)
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
