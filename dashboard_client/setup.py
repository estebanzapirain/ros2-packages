from setuptools import find_packages, setup

package_name = 'dashboard_client'

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
    description='Recibe un destino por MQTT, topic Destinos, ejecuta la acción gotoxy hasta cumplir la meta. Controla el estado de goal_pending.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        'dash_cli = dashboard_client.dash_client:main',
        ],
    },
)
