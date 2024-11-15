#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include <WebServer.h>

extern WebServer server;

void startLightControl();
void handleLightOn();
void handleLightOff();
void handleKitchenOn();
void handleKitchenOff();
void handleOptions();
void addCorsHeaders();

#endif // LIGHTCONTROL_H
