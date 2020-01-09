#include "Security.h"
#include <stdlib.h>
#include "Outputs.h"
#include "Inputs.h"
#include "WifiConn.h"
#define NULL_PTR 0U
uint8_t inputPin;
uint8_t buzzer=10;
uint16_t counter=1500;
//char* pwd;


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


void SecurityMainFunction()
{
    motion_detection();
    keypad.getKey();
    if (motionStatus == true)
    {

        if(counter==0)
        {
            analogWrite(buzzer, 250);
            counter = 1500;
            Serial.println("15s");
        }
        else
        {
            counter--;
        }
    }

    /* infoPgSecurity();

        Serial.println("Mai departe");
        pwd=parole;
        //int cnt=pospass/4;


      Serial.println(pwd);
    */
}




