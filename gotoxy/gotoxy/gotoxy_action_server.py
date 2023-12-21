#!/usr/bin/env python3
# Copyright 2019 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.import time

import time

from gotoxy_interface.action import GoToXY

import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node

fps = 2

class GoToXYActionServer(Node):

    def __init__(self):
        super().__init__('gotoxy_action_server')
        self._action_server = ActionServer(
            self,
            GoToXY,
            'gotoxy',
            self.execute_callback)

    def execute_callback(self, goal_handle):
        # Acá hace todo
        # Tiene que ir moviendo los motores y reportando feedback de la distancia al objetivo
        # goal_handle.request.goal_x es la posicion destino
         
        #Meta en proceso
        self.get_logger().info('Executing goal...')
        feedback_msg = GoToXY.Feedback()
        #Condiciones iniciales (tienen que ser dónde arranca el robot)
        feedback_msg.partial_x = 0
        feedback_msg.partial_y = 0
        
        while (feedback_msg.partial_x < goal_handle.request.goal_x):
        #Dar feedback de la posición actual del robot (o la distancia al destino)
                feedback_msg.partial_x = feedback_msg.partial_x + 1
                self.get_logger().info('Feedback: {0}'.format(feedback_msg.partial_x))
                goal_handle.publish_feedback(feedback_msg)
                time.sleep(1/fps)
#       for i in range(1, goal_handle.request.order):
#             feedback_msg.partial_sequence.append(
#                 feedback_msg.partial_sequence[i] + feedback_msg.partial_sequence[i-1])


        goal_handle.succeed()

        result = GoToXY.Result()
        result.final_x = feedback_msg.partial_x
        result.final_y = feedback_msg.partial_y
        return result


def main(args=None):
    rclpy.init(args=args)

    gotoxy_action_server = GoToXYActionServer()

    try:
        rclpy.spin(gotoxy_action_server)
    except KeyboardInterrupt:
        pass


if __name__ == '__main__':
    main()
