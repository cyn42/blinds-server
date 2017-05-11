/**
 * blinds-server
 *
 * The brains of the automated blinds. Provides a web interface
 * and a REST API for control of the blinds.
 *
 * First Drop: Get it working with all code in one file. Then make it pretty
 */
#include "Arduino.h"
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <config.h>

const char* ssid = WIFISSID;
const char* password = WIFIPASSWORD;

String webString="";     // String to display

ESP8266WebServer server(80);

void handle_root() {
  server.send(200, "text/plain", "Hello from the blinds server, control from /blinds/control");
  delay(100);
}

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

  server.on("/", handle_root);

  server.on("/blinds/control", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    webString="Control the Blinds";
    server.send(200, "text/plain", webString);               // send to someones browser when asked
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
}
