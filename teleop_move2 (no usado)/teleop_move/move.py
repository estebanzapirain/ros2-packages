import rclpy
from rclpy.node import Node
from geometry_msgs import Twist

# Biblioteca de comunicación serie RPi-Arduino
import serial
arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
arduino.reset_input_buffer()


class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            String,
            'topic',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
            self.logger().info(msg)
#         comando = "Comando ID0" + str(request.id) + "t " + str(request.left) + " " + str(request.right) + " " + str(request.time) + "\r\n" # para el logger
#         arduino.write(b'ID0')
#         arduino.write(str(request.id).encode())
#         arduino.write(b't ')
#         arduino.write(str(request.left).encode())
#         arduino.write(b' ')
#         arduino.write(str(request.right).encode())
#         arduino.write(b' ')
#         arduino.write(str(request.time).encode())
#         arduino.write(b'\r')
#         valor = arduino.readline()
#         if valor == "OK":
#                 response.ok = 1
#  
def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
