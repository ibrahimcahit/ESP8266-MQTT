// Open-Source ESP8266 code created by Ibrahim Cahit Ozdemir
//
// https://github.com/ibrahimcahit

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// Wi-Fi manager makes Wi-Fi connection simple for ESP8266. It's automaticly connects to saved networks. 
#include <WiFiManager.h> 


#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Select right sensor type for better readings
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin D2
DHT dht(dht_dpin, DHTTYPE); 


IPAddress mqtt_server(000, 000, 0, 00); // Enter your localy running MQTT brokers IP address

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
String relay;
String strTemp;
String strHumi;

void setup_wifi() {
  delay(2000);
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Node MCU");
}

void callback(char* topic, byte* payload, unsigned int length) {
  
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      // Subscribtion is not necessary
      client.subscribe("ESP8266");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
    
}

void setup() {
  Serial.begin(115200);     
  pinMode(dht_dpin, INPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // "ESP8266/Temp" is the topic I used for publishing sensor readings. You can change it with whatever you like.
  client.publish("ESP8266/Temp", String(t).c_str(), true); 
  client.publish("ESP8266/Humi", String(h).c_str(), true);
  delay(60000);
}
