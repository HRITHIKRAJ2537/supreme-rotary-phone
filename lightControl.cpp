#include <WebServer.h>
#include "lightControl.h"

// Create a web server object that listens on port 80
extern WebServer server;

// Pin configurations for the lights
const int livingRoomLightPin = 18; // GPIO 18
const int kitchenLightPin = 19;    // GPIO 19

// Variables to store light statuses
bool livingRoomLightOn = false;
bool kitchenLightOn = false;

void startLightControl() {
  // Set pin modes for lights
  pinMode(livingRoomLightPin, OUTPUT);
  pinMode(kitchenLightPin, OUTPUT);

  // Initialize the lights in OFF state
  digitalWrite(livingRoomLightPin, LOW);
  digitalWrite(kitchenLightPin, LOW);

  // Define the routes for light control with CORS support
  server.on("/light-on", HTTP_POST, handleLightOn);
  server.on("/light-off", HTTP_POST, handleLightOff);
  server.on("/kitchen-on", HTTP_POST, handleKitchenOn);
  server.on("/kitchen-off", HTTP_POST, handleKitchenOff);

  // Handle preflight OPTIONS requests for CORS
  server.on("/light-on", HTTP_OPTIONS, handleOptions);
  server.on("/light-off", HTTP_OPTIONS, handleOptions);
  server.on("/kitchen-on", HTTP_OPTIONS, handleOptions);
  server.on("/kitchen-off", HTTP_OPTIONS, handleOptions);

  server.begin();
}

void addCorsHeaders() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

void handleOptions() {
  addCorsHeaders();
  server.send(204);  // No Content response for OPTIONS
}

void handleLightOn() {
  livingRoomLightOn = true;
  digitalWrite(livingRoomLightPin, HIGH);  // Turn on the light
  addCorsHeaders();
  server.send(200, "text/plain", "Living room light is ON");
}

void handleLightOff() {
  livingRoomLightOn = false;
  digitalWrite(livingRoomLightPin, LOW);  // Turn off the light
  addCorsHeaders();
  server.send(200, "text/plain", "Living room light is OFF");
}

void handleKitchenOn() {
  kitchenLightOn = true;
  digitalWrite(kitchenLightPin, HIGH);  // Turn on the kitchen light
  addCorsHeaders();
  server.send(200, "text/plain", "Kitchen light is ON");
}

void handleKitchenOff() {
  kitchenLightOn = false;
  digitalWrite(kitchenLightPin, LOW);  // Turn off the kitchen light
  addCorsHeaders();
  server.send(200, "text/plain", "Kitchen light is OFF");
}

