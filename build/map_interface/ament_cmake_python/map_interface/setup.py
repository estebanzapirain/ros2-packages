from setuptools import find_packages
from setuptools import setup

setup(
    name='map_interface',
    version='0.0.1',
    packages=find_packages(
        include=('map_interface', 'map_interface.*')),
)
