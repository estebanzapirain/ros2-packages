# Copyright 2016 Open Source Robotics Foundation, Inc.
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

import rclpy
from rclpy.node import Node

from std_msgs.msg import String

import RPi.GPIO as gpio
import time

# Seteando el modo BOARD, la numeración de las salidas es la de la placa
pin_led = 13
gpio.setmode(gpio.BOARD)

# Seteando el modo BCM, la numeración de las salidas es la de GPIO
# pin_led = 27
# gpio.setmode(gpio.BCM)


gpio.setup(pin_led,gpio.OUT)

class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(String, 'topic', 10)
        timer_period = 2.0  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.on = False

    def timer_callback(self):
        msg = String()
        if self.on:
            gpio.output(pin_led,False)
            msg.data = "Output OFF"
            self.on = False
        else:
            gpio.output(pin_led,True)
            msg.data = "Output ON"
            self.on = True            
        self.publisher_.publish(msg)
        
        
def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
