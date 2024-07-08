# import file with mqtt connection functions and config
import MQTT 

def run():
    client = MQTT.connect()
    MQTT.subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()
