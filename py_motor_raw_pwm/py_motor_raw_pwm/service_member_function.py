from pwm_interface.srv import SetSpeeds

import rclpy
from rclpy.node import Node

# Biblioteca de comunicación serie RPi-Arduino
import serial
arduino = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)
arduino.reset_input_buffer()


class MinimalService(Node):

    def __init__(self):
        super().__init__('minimal_service')
        

        # Definición del servicio: interfaz, name y callback
        self.srv = self.create_service(SetSpeeds, 'set_speeds', self.set_speeds_callback)
    
    # Callback del servicio. La request son los 2 enteros a sumar y la response es el resultado
    def set_speeds_callback(self, request, response):
        comando = "o " + str(request.left) + " " + str(request.right) + "\r\n"
        arduino.write(b'o ')
        arduino.write(str(request.left).encode())
        arduino.write(b' ')
        arduino.write(str(request.right).encode())
        arduino.write(b'\r\n')
        valor = arduino.readline().decode('ascii').rstrip()
        self.get_logger().info(comando)
        if valor == "OK":
                response.ok = 1
                self.get_logger().info('Velocidades Izquierda: %d Derecha: %d' % (request.left, request.right))

        return response


def main():
    rclpy.init()

    minimal_service = MinimalService()

    rclpy.spin(minimal_service)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
