# Red ROS - Red de Robots colaborativos basada en ROS
## Objetivo

Crear un conjunto de robots que actúen como un equipo, moviéndose en un área coordinadamente siguiendo un comportamiento grupal asignado, por ejemplo:
* llevar un paquete de un lado a otro, donde cada robot tenga un área asignada
* jugar al fútbol
* etc

Cada robot será un robot móvil con hardware típico de Arduino, con 2 motores y el firmware controlador ROS Arduino Bridge. La comunicación será inalámbrica, puede ser por medio de las placas con Arduino Nano y NRF240 (¿?) que hay en el Lab.
La coordinación será provista por un procesador central RPi conectado a una cámara cenital de tipo Pixy Cam, que tiene un software incorporado de reconocimiento de objetos y colores. Para facilitar su uso los robots y los objetos que quieran ser detectados necesitan un indicador de color identificativo en su parte superior.
El software central será un ROS con nodos correspondientes a los procesos de cada uno de los robots, y en donde se llevará a cabo el procesamiento de las posiciones de cada robot (y de cada objeto en el área, ej: caja, pelota) y se emitirán las instrucciones de movimiento. Se comportará como un único robot distribuido, donde cada robot móvil es un apéndice del robot principal. El ROS actúa de enlace de comunicación, a modo de red entre los robots.
