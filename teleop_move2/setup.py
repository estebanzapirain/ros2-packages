from setuptools import find_packages, setup

package_name = 'setspeeds_server'

setup(
    name=package_name,
    version='0.0.0',
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
    description='Teleop Keyboard move',
    license='Apache 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'Move = teleop_move.move:main',
        ],
    },
)
