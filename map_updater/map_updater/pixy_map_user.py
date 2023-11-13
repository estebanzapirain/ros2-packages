import rclpy
from rclpy.node import Node

from map_interface.msg import Block


class MapSubscriber(Node):

    def __init__(self):
        super().__init__('map_subscriber')
        self.subscription = self.create_subscription(
            Block,
            'map',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('id= "%d"' % msg.id)
        self.get_logger().info('x= "%d"' % msg.x)
        self.get_logger().info('y= "%d"' % msg.y)
        self.get_logger().info('width= "%d"' % msg.width)
        self.get_logger().info('height= "%d"' % msg.height)

def main(args=None):
    rclpy.init(args=args)

    map_subscriber = MapSubscriber()

    rclpy.spin(map_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    map_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
