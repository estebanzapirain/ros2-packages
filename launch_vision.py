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
    node4 = Node(
        package="goal_updater",
        executable="goal_upd"
    )
    ld.add_action(node1)
    ld.add_action(node2)
    ld.add_action(node3)
    ld.add_action(node4)
    
    return ld
