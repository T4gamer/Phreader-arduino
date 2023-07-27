#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ph";
const char* password = "12345678";

ESP8266WebServer server(80);

typedef union {  float number;  
  uint8_t bytes[4];  } FLOATUNION_t;
FLOATUNION_t float1, float2; 

void clearSerialBuffer() {
  while (Serial.available() > 0) {
    Serial.read();
  }
}


void handleEndpoint1() {
  clearSerialBuffer();
  Serial.readBytes(float1.bytes, 4);
  Serial.readBytes(float2.bytes, 4);
  server.send(200, "text/plain", String(float1.number));
}
void handleEndpoint2() {
  clearSerialBuffer();
  Serial.readBytes(float1.bytes, 4);
  Serial.readBytes(float2.bytes, 4);
  server.send(200, "text/plain", String(float2.number));
}

  
void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/value1", handleEndpoint1);
  server.on("/value2", handleEndpoint2);

  server.begin();
}

void loop() {
  server.handleClient();
}
