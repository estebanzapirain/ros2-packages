from pwm_interface.srv import SetSpeedsT

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
        self.srv = self.create_service(SetSpeedsT, 'set_speeds', self.set_speeds_callback)

# Callback del servicio. La request son los 2 enteros a sumar y la response es el resultado
    def set_speeds_callback(self, request, response):

# Comando para el Arduino ROS Bridge: "t [left] [right] [time]" 
        comando = "Comando ID0" + str(request.id) + "t " + str(request.left) + " " + str(request.right) + " " + str(request.time) + "\r\n" # para el logger
        arduino.write(b'ID0')
        arduino.write(str(request.id).encode())
        arduino.write(b't ')
        arduino.write(str(request.left).encode())
        arduino.write(b' ')
        arduino.write(str(request.right).encode())
        arduino.write(b' ')
        arduino.write(str(request.time).encode())
        arduino.write(b'\r')
        #self.get_logger().info('ID: %s Velocidades Izquierda: %s Derecha: %s' % (str(request.id).encode(), str(request.left).encode(), str(request.right).encode()))
        # valor = arduino.readline().decode('ascii').rstrip()
        valor = arduino.readline()
        #self.get_logger().info(comando)
        if valor == "OK":
                response.ok = 1
        #self.get_logger().info('ID: %d Velocidades Izquierda: %d Derecha: %d Tiempo: %d' % (request.id, request.left, request.right, request.time))

        return response


def main():
    rclpy.init()

    minimal_service = MinimalService()

    rclpy.spin(minimal_service)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
