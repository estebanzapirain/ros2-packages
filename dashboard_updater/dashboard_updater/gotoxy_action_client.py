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
# limitations under the License.

# import interfaces
from gotoxy_interface.action import GoToXY #Gotoxy client
from map_interface.msg import Goal #goal publisher

# to get arguments from system
import sys

import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
import threading
import time

#update rate
fps = 10

#init variables
goal_x = 0
goal_y = 0
goal_angle = 0

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
        result = future.result().result
        self.get_logger().info('FinalX: {0}'.format(result.final_x))
        self.get_logger().info('FinalY: {0}'.format(result.final_y))
        rclpy.shutdown()

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        self.get_logger().info('Received feedback: {0}'.format(feedback.partial_angle))

#Publisher to topic "robot_pos", informs (x,y) and angle of robots in each frame
class GoalPublisher(Node):

    def __init__(self):
        super().__init__('goal_publisher')
 
        self.publisher_ = self.create_publisher(Goal, 'goal', 10) # (message, topic, queue_size)
 
        timer_period = 1/fps
        print(timer_period)
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        global goal_x, goal_y, goal_angle
        
        #Init new mesagge
        msg = Goal()
        #if MapSubscriber got new data from a robot
        msg.x = goal_x
        msg.y = goal_y
        msg.angle = goal_angle
        
        #Publish
	#print(msg.robot_id, msg.frame, msg.x, msg.y, msg.angle)
        self.publisher_.publish(msg)
        #self.get_logger().info('Goal: "%s"' % msg)


def main(args=None):
    global goal_x, goal_y, goal_angle
    
    rclpy.init(args=args)
    
    goal_x = int(sys.argv[1])
    goal_y = int(sys.argv[2])
    goal_angle = int(sys.argv[3])
    
   #Start nodes 
    action_client = GoToXYClient()
    goal_publisher = GoalPublisher()

    #Executor
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(action_client)
    executor.add_node(goal_publisher)
    # Spin in a separate thread
    executor_thread = threading.Thread(target=executor.spin, daemon=True)
    executor_thread.start()
    
    
    rate = goal_publisher.create_rate(fps)
    

    
    action_client.send_goal(goal_x, goal_y, goal_angle)

    rclpy.spin(action_client)


    try:
        while rclpy.ok():
            #print('Help me body, you are my only hope')
            rate.sleep()
    except KeyboardInterrupt:
        pass
        
if __name__ == '__main__':
    main()
