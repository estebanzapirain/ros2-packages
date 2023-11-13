# ROS2-Pixy-Net
Red de robots colaborativos basada en ROS2 y la PixyCam

## Objetivo

* Crear un conjunto de robots que actúen como un equipo, moviéndose en un área coordinadamente siguiendo un comportamiento grupal asignado, por ejemplo:
llevar un paquete de un lado a otro, donde cada robot tenga un área asignada
jugar al fútbol
etc
* Cada robot será un robot móvil con hardware típico de Arduino, con 2 motores y el firmware controlador ROS Arduino Bridge. La comunicación será inalámbrica, puede ser por medio de las placas con Arduino Nano y NRF240 (¿?) que hay en el Lab.
* La coordinación será provista por un procesador central RPi conectado a una cámara cenital de tipo Pixy Cam, que tiene un software incorporado de reconocimiento de objetos y colores. Para facilitar su uso los robots y los objetos que quieran ser detectados necesitan un indicador de color identificativo en su parte superior.
* El software central será un ROS con nodos correspondientes a los procesos de cada uno de los robots, y en donde se llevará a cabo el procesamiento de las posiciones de cada robot (y de cada objeto en el área, ej: caja, pelota) y se emitirán las instrucciones de movimiento. Se comportará como un único robot distribuido, donde cada robot móvil es un apéndice del robot principal. El ROS actúa de enlace de comunicación, a modo de red entre los robots.

## Planificación
* Aprender a usar la cámara Pixy. Reconocer una signature de color.
* Conectarlo con la Raspberry.
* Meterlo en un nodo ROS. Podría ser un publisher que vaya mandando las coordenadas de la posición.
* Hacer un script del tipo “llegar a la meta”. Tomar la posición del robot y de otra marca, y darle comandos hasta llegar (nodo “action”?)
* Ver de levantar varios nodos del mismo tipo, con cada uno correspondiendo a un robot. Se pueden usar las placas con Arduino Nano y NRF240 (¿?) que hay en el Lab para identificarlos. Podría ser que en el mensaje haya un campo id con el número de dispositivo.
* Crear un nodo de procesamiento central que tome las posiciones de los distintos robots y decida el comportamiento grupal.

## Nodo robot móvil:

### Package: py_motor_raw_pwm
**Tipo de comunicación:** client-service <br>
**Objetivo:** Modifica las velocidades de los motores, a lazo abierto (sin PID). <br>
**Interfaz:** pwm_interface <br>
SetSpeeds.srv <br>
uint8 left <br>
uint8 right <br>
— <br>
int8 ok <br>

**Nodos:** <br>
**client:** envía un request con 2 parámetros, left y right. <br>
**service:** se comunica con Arduino ROS Bridge, comando “o {left} {right}” y devuelve un 1 en ok si se comunicó bien. <br>


## Pixy:

### Package: map_updater
**Tipo de comunicación:** pub-sub <br>
**Objetivo:** Publica los bloques detectados por la PixyCam. <br>
**Interfaz:** block <br>
int64 id <br>
int64 x <br>
int64 y <br>
int64 width <br>
int64 height <br>

**Nodos:** <br>
**map_user:** escucha lo publicado por el map_getter <br>
**map_getter:** se comunica con Arduino Pixy-ROS Bridge, comando “m” y publica el bloque separado en campos. <br>


