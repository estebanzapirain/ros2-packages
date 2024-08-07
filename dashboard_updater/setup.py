from setuptools import find_packages, setup

package_name = 'dashboard_updater'

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
    description='Nodo que envía la información de los elementos captados por la cámara, al dashboard',
    license='Apache 2',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        'dash_upd = dashboard_updater.dash_updater:main',  
        ],
    },
)
