from setuptools import find_packages
from setuptools import setup

setup(
    name='pwm_interface',
    version='0.0.0',
    packages=find_packages(
        include=('pwm_interface', 'pwm_interface.*')),
)
