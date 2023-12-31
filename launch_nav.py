from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    node1 = Node(
        package="py_motor_raw_pwm",
        executable="SpeedSetter",
    )
    node2 = Node(
        package="gotoxy",
        executable="gotoxy_server"
    )
    ld.add_action(node1)
    ld.add_action(node2)
    return ld
