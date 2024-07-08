# sub.py
import time
from umqtt.simple import MQTTClient

SERVER="mqtt.fi.mdp.edu.ar"
ClientID = f'raspberry-sub-{time.time_ns()}'
user = ""
password = ""
topic = "/Posiciones/" #"/Destino/"
msg = b'{"msg":"hello"}'

def sub(topic, msg):
    print('received message %s on topic %s' % (msg, topic))

def main(server=SERVER):
    client = MQTTClient(ClientID, server, 1883, user, password)
    client.set_callback(sub)
    client.connect()
    print('Connected to MQTT Broker "%s"' % (server))
    client.subscribe(topic)
    while True:
        if True:
            client.wait_msg()
        else:
            client.check_msg()
            time.sleep(1)

if __name__ == "__main__":
    main()
