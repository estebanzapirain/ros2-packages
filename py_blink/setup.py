from setuptools import find_packages, setup

package_name = 'py_blink'

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
    maintainer_email='robot1@fi.mdp.edu.ar',
    description= 'Blink led con python',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
		'talker = py_blink.publisher_member_function:main',
		'listener = py_blink.subscriber_member_function:main',
        ],
    },
)
