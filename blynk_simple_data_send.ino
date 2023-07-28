#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ph";
const char* password = "12345678";

ESP8266WebServer server(80);

typedef union {  float number;  
  uint8_t bytes[4];  } FLOATUNION_t;
FLOATUNION_t float1, float2;

const int bufferSize = 8;
const int subsetSize = 4;
byte buffer[bufferSize];
int bufferIndex = 0;
int startIndex = bufferSize - subsetSize;

void clearSerialBuffer() {
  while (Serial.available() > 8) {
    Serial.read();
  }
}

void handleEndpoint1() {
  clearSerialBuffer();
  Serial.readBytes(buffer,8);
//  if (Serial.available()) {
//    byte incomingByte = Serial.read();
//    buffer[bufferIndex] = incomingByte;
//    bufferIndex++;
//    if (bufferIndex == bufferSize) {
//      bufferIndex = 0;
//    }
//  }
  memcpy(float1.bytes, buffer, subsetSize);
  server.send(200, "text/plain", String(float1.number));
}
void handleEndpoint2() {
  clearSerialBuffer();
  Serial.readBytes(buffer,8);
//  if (Serial.available()) {
//    byte incomingByte = Serial.read();
//    buffer[bufferIndex] = incomingByte;
//    bufferIndex++;
//    if (bufferIndex == bufferSize) {
//      bufferIndex = 0;
//    }
//  }
  memcpy(float2.bytes, &buffer[startIndex], subsetSize);
  server.send(200, "text/plain", String(float2.number));
}

void handleEndpoint3() {
  ESP.restart();
}
void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/value1", handleEndpoint1);
  server.on("/value2", handleEndpoint2);
  server.on("/rest", handleEndpoint3);

  server.begin();
}

void loop() {
  server.handleClient();
}
