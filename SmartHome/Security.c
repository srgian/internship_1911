#include "Security.h"
#include <stdlib.h>
#include "Outputs.h"
#include "Inputs.h"
#include "WifiConn.h"
#define NULL_PTR 0U
uint8_t inputPin;
uint8_t buzzer=10;
uint16_t counter=1500;

char *pwds;
uint8_t pwdCnt=0;
//char *parole;

void SecurityInit()
{
    HWDigitalMode(buzzer,OUTPUT);
    HWDigitalWrite(buzzer, HIGH);
    HWDigitalMode(pirState,INPUT);
    lcdSecurity.init();
    lcdSecurity.backlight();
    lcdSecurity.setCursor(1, 0);
    lcdSecurity.print("Enter code:");
    lcdSecurity.setCursor(0, 1);
    Serial.begin(9600);
    keypad.addEventListener((void (*)(char))keypadEvent);
}



void SecurityReloadPasswords(){

    pwdCnt=pos/4;
    Serial.print(pwdCnt);

    pwds=(char*)malloc(pwdCnt*4*sizeof(char));

    if(pwds!=NULL_PTR)
    {
    //    for(int i=0; i<pwdCnt;i++)
      //  {
            //char x[4]={0x30+i,0x31+i,0x32+i,0x33+i};
            //memcpy(pwds, &parole, 4);
            //*(pwds+(i*4))= dataPgSecurity;
        //}
    }

    for(int i=0; i<4*pwdCnt; i++)
    {
        printf("%d: 0x%02X\n", i, *(pwds+i));
    }
}
void SecurityMainFunction(){

    motion_detection();

    keypad.getKey();

    if (motionStatus == true)
    {

        if(counter==0){
            analogWrite(buzzer, 250);
            counter = 1500;
            Serial.println("15s");
        }
        else{
            counter--;
        }
    }
    if(statusWifi == 1){
        infoPgSecurity();
        Serial.print(parole);
        SecurityReloadPasswords();
    }
}




