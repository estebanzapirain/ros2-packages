from setuptools import find_packages, setup

package_name = 'robot_positions'

setup(
    name=package_name,
    version='0.0.1',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robot1',
    maintainer_email='estebanzapirain@gmail.com',
    description='Gets map of objects and returns robot position and facing angle',
    license='Apache 2',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        'robot_pos_updater = robot_positions.__init__:main',        
        ],
    },
)
