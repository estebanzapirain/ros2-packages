from blinks_interface.srv import Blinks

import rclpy
from rclpy.node import Node

# Biblioteca de comunicación serie RPi-Arduino
import serial
arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
arduino.reset_input_buffer()


class MinimalService(Node):

    def __init__(self):
        super().__init__('minimal_service')


# Definición del servicio: interfaz, name y callback
        self.srv = self.create_service(Blinks, 'blinks', self.blinks_callback)

# Callback del servicio. La request son los 2 enteros a sumar y la response es el resultado
    def blinks_callback(self, request, response):

# Comando para el Arduino ROS Bridge: "l [number] [delay]" 
        comando = "Comando ID0" + str(request.id) + "l " + str(request.number) + " " + str(request.delay) + "\r\n" # para el logger
        arduino.write(b'ID0')
        arduino.write(str(request.id).encode())
        arduino.write(b'l ')
        arduino.write(str(request.number).encode())
        arduino.write(b' ')
        arduino.write(str(request.delay).encode())
        arduino.write(b'\r')

        valor = arduino.readline()
        self.get_logger().info(comando)
        if valor == "OK":
                response.ok = 1
        #self.get_logger().info('ID: %d Velocidades Izquierda: %d Derecha: %d' % (request.id, request.left, request.right))

        return response


def main():
    rclpy.init()

    minimal_service = MinimalService()

    rclpy.spin(minimal_service)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
