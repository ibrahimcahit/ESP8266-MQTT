// Open-Source ESP8266 code created by Ibrahim Cahit Ozdemir
//
// https://github.com/ibrahimcahit

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update with your Wi-Fi 
const char* ssid = "update_with_your_ssid";
const char* password = "update_with_your_password";

// Enter your localy running MQTT brokers IP address
IPAddress mqtt_server(000, 000, 0, 00);


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
String relay;
String strTopic;
String strPayload;

void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  strTopic = String((char*)topic);

  // you can change topic with whatever you want.
  if(strTopic == "ESP8266")
    {
    relay = String((char*)payload);
    if(relay == "relay_1_on")  { digitalWrite(D1, LOW); }
    if(relay == "relay_1_off") { digitalWrite(D1, HIGH); }
    
    if(relay == "relay_2_on")  { digitalWrite(D2, LOW); }
    if(relay == "relay_2_off") { digitalWrite(D2, HIGH); }
    
    if(relay == "relay_3_on")  { digitalWrite(D5, LOW); }
    if(relay == "relay_3_off") { digitalWrite(D5, HIGH); }
    
    if(relay == "relay_4_on")  { digitalWrite(D6, LOW); }
    if(relay == "relay_4_off") { digitalWrite(D6, HIGH); }
    
    if(relay == "relay_all_on")  { 
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D5, LOW);
      digitalWrite(D6, LOW);
    }
    if(relay == "relay_all_off") { 
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D5, HIGH);
      digitalWrite(D6, HIGH);
      }
    }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      
      // you can change topic with whatever you want.
      client.subscribe("ESP8266");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  client.publish("ESP8266", "NodeMCU Connected!");  
}

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
