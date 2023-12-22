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

from gotoxy_interface.action import GoToXY

# to get arguments from system
import sys

import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node


class GoToXYClient(Node):

    def __init__(self):
        super().__init__('gotoxy_client')
        self._action_client = ActionClient(self, GoToXY, 'gotoxy')

    def send_goal(self, x, y, angle):
        goal_msg = GoToXY.Goal()
        goal_msg.goal_x = x
        goal_msg.goal_y = y
        goal_msg.angle = angle

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
        self.get_logger().info('Result: {0}'.format(result.final_x))
        rclpy.shutdown()

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        self.get_logger().info('Received feedback: {0}'.format(feedback.partial_x))


def main(args=None):
    rclpy.init(args=args)

    action_client = GoToXYClient()
    
    goal_x = int(sys.argv[1])
    goal_y = int(sys.argv[2])
    goal_angle = int(sys.argv[3])
    
    action_client.send_goal(goal_x, goal_y, goal_angle)

    rclpy.spin(action_client)


if __name__ == '__main__':
    main()
