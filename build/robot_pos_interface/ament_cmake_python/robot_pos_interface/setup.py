from setuptools import find_packages
from setuptools import setup

setup(
    name='robot_pos_interface',
    version='0.0.0',
    packages=find_packages(
        include=('robot_pos_interface', 'robot_pos_interface.*')),
)
