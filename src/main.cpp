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

String webString="";     // String to display

AsyncWebServer server(80);

void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Blinds Control Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello from the blinds server, control from /blinds/control");
  });

  server.on("/blinds/control",  HTTP_GET, [](AsyncWebServerRequest *request){
    webString="Control the Blinds";
    request->send(200, "text/plain", webString);               // send to someones browser when asked
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  //server.handleClient();
}
