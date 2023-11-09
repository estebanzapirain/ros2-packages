import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class MapSubscriber(Node):

    def __init__(self):
        super().__init__('map_subscriber')
        self.subscription = self.create_subscription(
            String,
            'map',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info(msg.data)
        


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
