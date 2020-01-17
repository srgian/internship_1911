#include "WifiConn.h"
#include <Arduino.h>
#include <WString.h>

uint8_t connectWifi = 0;
uint8_t requestData = 0;
uint8_t statusWifi = 0;

char *parole=NULL;
char *lumini=NULL;
char *confort=NULL;

size_t pospass = 0;
size_t poslgh = 0;
size_t poscnf = 0;

char netwpass[] = "%samsung%xena8583%1";//"%3" reprezinta nr pg
char pgLights[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/lights.php";
char pgConfort[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/confort.php";
char pgSecurity[] = "%www.bizkit.eu%GET /~arobs-i1911/cfg/security.php";
char pgToUpload[] = "%bizkit.eu%POST /~arobs-i1911/cfg/status.php HTTP/1.1";


uint8_t stopInit = 0;

String data = "";
String d = "%";

void uploadData() {

  String data = d + tempsts + d + alarmasts /*+ d + lightssts*/;

  uint8_t raspuns;
  Serial.print(pgToUpload);

  for (;;) {
    while (!Serial.available()) {}
    raspuns = Serial.read();
    if (raspuns == 1) {
      break;
    }
    Serial.print(data);
  }
}

void infoPgSecurity()
{
    Serial.print(pgSecurity);

    int c = 0;
    char dataPgSecurity[200];

    for (;;)
    {
        while (!Serial.available()) {}
        c = (char)Serial.read();
        if (c == -1)
            continue;   // no input
        if (pospass < sizeof dataPgSecurity - 1)
        {
            dataPgSecurity[pospass++] = c;
        }
        if (c == '%')           // end of string
        {
            break;
        }
    }
    if (parole != NULL)
    {
        free(parole);
    }
    parole=(char*)malloc(pospass*sizeof(char)+1);
    if (parole != NULL)
    {
        memcpy(parole, dataPgSecurity, pospass);
        *(parole+pospass)='\0';
    }
}

void infoPgLights()
{
    Serial.print(pgLights);

    int c = 0;
    char dataPgLights[200];

    for (;;)
    {
        while (!Serial.available()) {}
        c = (char)Serial.read();
        if (c == -1)
            continue;   // no input
        if (poslgh < sizeof dataPgLights - 1)
        {
            dataPgLights[poslgh++] = c;
        }
        if (c == '%')           // end of string
        {
            break;
        }
    }
    if (lumini != NULL)
    {
        free(lumini);
    }
    lumini=(char*)malloc(poslgh*sizeof(char)+1);
    if (lumini != NULL)
    {
        memcpy(lumini, dataPgLights, poslgh);
        *(lumini+poslgh)='\0';
    }
}

void infoPgConfort()
{
    Serial.print(pgConfort);

    int c = 0;
    char dataPgConfort[200];

    for (;;)
    {
        while (!Serial.available()) {}
        c = (char)Serial.read();
        if (c == -1)
            continue;   // no input
        if (poscnf < sizeof dataPgConfort - 1)
        {
            dataPgConfort[poscnf++] = c;
        }
        if (c == '%')           // end of string
        {
            break;
        }
    }
    if (confort != NULL)
    {
        free(confort);
    }
    confort=(char*)malloc(poscnf*sizeof(char)+1);
    if (confort != NULL)
    {
        memcpy(confort, dataPgConfort, poscnf);
        *(confort+poscnf)='\0';
    }
}

void connToWifi()
{

    for (;;)
    {
        connectWifi = 1;
        Serial.write(connectWifi);//Se cere conectarea la wifi
        while (!Serial.available()) {} //se astepta cererea datatelor
        requestData = Serial.read();
        if (requestData == 1)
            ;
        //daca datele au fost cerute iesim din bucla
        {
            break;
        }
    }

    Serial.print(netwpass);//S-au trimis datele

    while (!Serial.available()) {} //se asteapta raspunsul conectarii
    statusWifi = Serial.read();
    if (statusWifi == 1) {
      //return 1;//Conectare Reusita!
    }
    if (statusWifi == 2) {
      //return 2;//Time Out!
    }
}
