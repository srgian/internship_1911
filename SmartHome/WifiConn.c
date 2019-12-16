#include "WifiConn.h"
#include <Arduino.h>

uint8_t connectWifi = 0;
uint8_t requestData = 0;
uint8_t statusWifi = 0;
uint8_t continuee = 1;
uint8_t stopp = 0;

char netwpass[] = "%AngeloA50%angeloangelo%3";//"%3" reprezinta nr pg
char pgLights[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/lights.php";
char pgConfort[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/confort.php";
char pgSecurity[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/security.php";

char dataPgLights[200];
char dataPgConfort[200];
char dataPgSecurity[200];

uint8_t stopInit = 0;
char response[200];

/*void setup() {
  Serial.begin(9600);
}*/

void infoPgSecurity() {
  Serial.print(pgSecurity);

  size_t pos = 0;
  for (;;) {
    while (!Serial.available()) {}
    int c = (char)Serial.read();
    if (c == -1) continue;   // no input
    if (pos < sizeof dataPgSecurity - 1) {
      dataPgSecurity[pos++] = c;
    }
    if (c == '%') {         // end of string
      break;
    }
  }
}

void infoPgLights() {

  Serial.print(pgLights);

  size_t pos = 0;
  for (;;) {
    while (!Serial.available()) {}
    int c = (char)Serial.read();
    if (c == -1) continue;   // no input
    if (pos < sizeof dataPgLights - 1) {
      dataPgLights[pos++] = c;
    }
    if (c == '%') {         // end of string
      break;
    }
  }
}

void infoPgConfort() {

  Serial.print(pgConfort);

  size_t pos = 0;
  for (;;) {
    while (!Serial.available()) {}
    int c = (char)Serial.read();
    if (c == -1) continue;   // no input
    if (pos < sizeof dataPgConfort - 1) {
      dataPgConfort[pos++] = c;
    }
    if (c == '%') {         // end of string
      break;
    }
  }
}

int connectToWifi() {
  for (;;) {
    connectWifi = 1;
    Serial.write(connectWifi);//Se cere conectarea la wifi
    while (!Serial.available()) {} //se astepta cererea datatelor
    requestData = Serial.read();
    if (requestData == 1); {//daca datele au fost cerute iesim din bucla
      break;
    }
  }

  Serial.print(netwpass);//S-au trimis datele

  while (!Serial.available()) {} //se asteapta raspunsul conectarii
  statusWifi = Serial.read();
  if (statusWifi == 1) {
    return 1;//Conectare Reusita!
  }
  if (statusWifi == 2) {
    return 2;//Time Out!
  }
}

void connToWifi() {/////////////////////////////////////////////LOOP//////////////////////////////////////////////

  if (connectToWifi() == 1) {//daca este conectat urmeaza cererea de info de pe dif pg
    infoPgSecurity();
    infoPgLights();
    infoPgConfort();

  }
  else {
    Serial.println("Conectare neusita!");
  }

Serial.println("");
Serial.println(dataPgSecurity);
Serial.println(dataPgLights);
Serial.println(dataPgConfort);
}
