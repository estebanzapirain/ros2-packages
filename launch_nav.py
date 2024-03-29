from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    node1 = Node(
        package="setspeeds_server",
        executable="SetSpeeds",
    )
    node2 = Node(
        package="gotoxy",
        executable="gotoxy_server"
    )
    node3 = Node(
        package="blinks",
        executable="blinks_sv"
    )
    
    ld.add_action(node1)
    ld.add_action(node2)
    ld.add_action(node3)
    return ld
