import sys

from blinks_interface.srv import Blinks
import rclpy
from rclpy.node import Node


class MinimalClientAsync(Node):

    def __init__(self):
        super().__init__('minimal_client_async')
        self.cli = self.create_client(Blinks, 'blinks')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('robot not available, waiting again...')
        self.req = Blinks.Request()

    def send_request(self, id, number, delay):
        self.req.id = id
        self.req.number = number
        self.req.delay = delay
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()


def main():
    rclpy.init()

    minimal_client = MinimalClientAsync()
    response = minimal_client.send_request(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))
    minimal_client.get_logger().info(
        'LED: id: %d number: %d delay: %d = %d' %
        (int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), response.ok))

    minimal_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
