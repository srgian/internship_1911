#ifndef WIFICONN_H
#define WIFICONN_H

#include <Arduino.h>
#include <inttypes.h>

void infoPgLights();
void infoPgConfort();
void connToWifi();
void infoPgSecurity();
void uploadData();

extern uint8_t alarmasts;
extern uint8_t tempsts;
//extern int lightssts;

#endif // WIFICONN_H
