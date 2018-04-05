/**
 * blinds-server
 *
 * The brains of the automated blinds. Provides a web interface
 * and a REST API for control of the blinds.
 *
 * First Drop: Get it working with all code in one file. Then make it pretty
 */
#include "Arduino.h"
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <cfg.h>

const char* ssid = WIFISSID;
const char* password = WIFIPASSWORD;

int connectingLED = 15;
int connectedLED = 14;

HardwareSerial Serial2( 2 );

#define SERIAL2_RX 12
#define SERIAL2_TX 13

String webString="";     // String to display

AsyncWebServer server(80);

void setup(void)
{
  //Serial.begin(9600); //Connection to motor controller
  Serial2.begin( 9600, SERIAL_8N1, SERIAL2_RX, SERIAL2_TX );
  delay(10);

  pinMode(connectingLED, OUTPUT);
  digitalWrite(connectingLED, HIGH);

  pinMode(connectedLED, OUTPUT);
  digitalWrite(connectedLED, LOW);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(connectingLED, LOW);
    delay(250);
    digitalWrite(connectingLED, HIGH);
    delay(250);

  }
  digitalWrite(connectedLED, HIGH);
  digitalWrite(connectingLED, LOW);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello from the blinds server, control from /blinds/[open|close|stop]");
  });

  server.on("/blinds/open",  HTTP_GET, [](AsyncWebServerRequest *request){
    Serial2.print('H');
    webString="Open the Blinds";
    request->send(200, "text/plain", webString);               // send to someones browser when asked
  });

  server.on("/blinds/close",  HTTP_GET, [](AsyncWebServerRequest *request){
    Serial2.print('L');
    webString="Close the Blinds";
    request->send(200, "text/plain", webString);               // send to someones browser when asked
  });

  server.on("/blinds/stop",  HTTP_GET, [](AsyncWebServerRequest *request){
    Serial2.print('S');
    webString="Stop the Blinds";
    request->send(200, "text/plain", webString);               // send to someones browser when asked
  });

  server.begin();

}

void loop(void)
{
  //server.handleClient();
}
