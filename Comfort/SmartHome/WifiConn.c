#include "WifiConn.h"
#include <Arduino.h>

uint8_t connectWifi = 0;
uint8_t requestData = 0;
uint8_t statusWifi = 0;
uint8_t continuee = 1;
uint8_t stopp = 0;

char *parole;
char *lumini;
char *confort;

size_t pos = 0;

char netwpass[] = "%AngeloA50%angeloangelo%3";//"%3" reprezinta nr pg
char pgLights[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/lights.php";
char pgConfort[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/confort.php";
char pgSecurity[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/security.php";


uint8_t stopInit = 0;

void infoPgSecurity() {

 Serial.print(pgSecurity);

  int c = 0;
  char dataPgSecurity[200];

  for (;;) {
    while (!Serial.available()) {}
    c = (char)Serial.read();
    if (c == -1) continue;   // no input
    if (pos < sizeof dataPgSecurity - 1) {
      dataPgSecurity[pos++] = c;
    }
    if (c == '%') {         // end of string
      break;
    }
  }
  if (parole == NULL)
    {
        free(parole);
    }
  parole=(char*)malloc(pos*sizeof(char));
  memcpy(parole, dataPgSecurity, pos);
  pos = 0;
}

void infoPgLights() {

  Serial.print(pgLights);

  int c = 0;
  char dataPgLights[200];

  for (;;) {
    while (!Serial.available()) {}
    c = (char)Serial.read();
    if (c == -1) continue;   // no input
    if (pos < sizeof dataPgLights - 1) {
      dataPgLights[pos++] = c;
    }
    if (c == '%') {         // end of string
      break;
    }
  }
  if (lumini == NULL)
    {
        free(lumini);
    }
  lumini=(char*)malloc(pos*sizeof(char));
  memcpy(lumini, dataPgLights, pos);
  pos = 0;
}

void infoPgConfort() {

  Serial.print(pgConfort);

  int c = 0;
  char dataPgConfort[200];

  for (;;) {
    while (!Serial.available()) {}
    c = (char)Serial.read();
    if (c == -1) continue;   // no input
    if (pos < sizeof dataPgConfort - 1) {
      dataPgConfort[pos++] = c;
    }
    if (c == '%') {         // end of string
      break;
    }
  }
  if (confort == NULL)
    {
        free(confort);
    }
  confort=(char*)malloc(pos*sizeof(char));
  memcpy(confort, dataPgConfort, pos);
  pos = 0;
}

void connectToWifi() {

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
  /*if (statusWifi == 1) {
    //return 1;//Conectare Reusita!
  }
  if (statusWifi == 2) {
    //return 2;//Time Out!
  }*/
}

void connToWifi() {/////////////////////////////////////////////LOOP//////////////////////////////////////////////

    connectToWifi();
  if (statusWifi == 1) {//daca este conectat urmeaza cererea de info de pe dif pg
    //Serial.print("Wifi conectat!");
  }
  else {
    Serial.println("Conectare nereusita!");
  }
}
