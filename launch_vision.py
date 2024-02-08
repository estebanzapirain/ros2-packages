from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    node1 = Node(
        package="map_updater_wired",
        executable="map_getter",
    )
    node2 = Node(
        package="map_viewer",
        executable="map_view"
    )
    node3 = Node(
        package="robot_positions",
        executable="robot_pos_updater"
    )
    ld.add_action(node1)
    ld.add_action(node2)
    ld.add_action(node3)
    return ld
