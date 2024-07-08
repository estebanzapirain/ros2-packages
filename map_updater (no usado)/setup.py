from setuptools import find_packages, setup

package_name = 'map_updater'

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
    description='Gets map of signatures from PixyCam',
    license='Apache 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
		'map_getter = map_updater.pixy_map_getter:main',

        ],
    },
)
