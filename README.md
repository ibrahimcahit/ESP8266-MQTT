# ESP8266
ESP8266 based MQTT applications 

## Prerequisites

You need to instal Arduino Software on your device.
Also you need to configure MQTT Broker, which runs localy. Most of my projects, I used Mosquitto

* [Arduino Software](https://www.arduino.cc/) 
* [Mosquitto Broker](https://mosquitto.org/)

## Projects
My Arduino based IoT projects.

### ESP8266 and DHT11 - Publish readings to MQTT Topic
With this code, you can read temperature and humidity values.
And you can publish them to the MQTT Broker.

Both DHT11 and DHT22 are compatible.

* [ESP8266 and DHT Code](https://github.com/ibrahimcahit/ESP8266/blob/master/ESP8266%20Arduino%20Codes/EPS8266_and_DHT11_MQTT.ino)


### ESP8266 and Relay module - Control 4 relay modules via MQTT
With this code, you can control your relay modules, connected to ESP8266, via MQTT.

4 relay modules used in this project

* [ESP8266 and Relay module Code](https://github.com/ibrahimcahit/ESP8266/blob/master/ESP8266%20Arduino%20Codes/EPS8266_and_relay_MQTT.ino)
