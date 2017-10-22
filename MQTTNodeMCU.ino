#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const int Led  = D2;

char message_buff[100];

const char* ssid = "ALMENDRA";
const char* password = "15345826kR";
const char* mqtt_server = "mqtt.clubarduino.cl";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(Led, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  int i = 0;
  for (i = 0; i < length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  String msgString = String(message_buff);

  if (msgString.equals("on")) {
    digitalWrite(Led, HIGH);
  } else if (msgString.equals("off")) {
    digitalWrite(Ledn , LOW);
  }

}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("NodeMCURaicerk")) {
      client.publish("Raicerk/Luz", "Hola, soy el nodemcu de Juan");
      client.subscribe("Raicerk/Luz");
    } else {
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

