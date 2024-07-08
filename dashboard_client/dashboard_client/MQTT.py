import paho.mqtt.client as mqtt_client
import time

#Configuración MQTT
server="localhost"
port = 1883
ClientID = f'raspberry-pub-{time.time_ns()}'
user = ""
password = ""
topic = "/Destinos/"
client = mqtt_client.Client(ClientID)
msg = b'{"msg":"hello"}'

#Conexión MQTT
def connect():
    print('Connected to MQTT Broker "%s"' % (server))
#     client = mqtt_client.Client(ClientID)
    client.connect(server, port)
    #client = MQTTClient(ClientID, server, 1884, user, password)
    #client.connect()
    return client

#Reconexión MQTT
def reconnect():
    print('Failed to connect to MQTT broker, Reconnecting...' % (server))
    time.sleep(5)
    client.reconnect()

#Recibir mensajes del topic
def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

    client.subscribe(topic)
    client.on_message = on_message