#include "Doorlock.h"
#include "Outputs.h"
#include "Inputs.h"
uint8_t doorbuzzer = 12;


void DoorlockInit()
{
    HWDigitalMode(doorbuzzer,OUTPUT);
    HWDigitalWrite(doorbuzzer, HIGH);
    myservo.attach(9);// attaching to the 9th pin
    analogWrite(doorbuzzer, 255);


    lcdDoorlock.init();
    lcdDoorlock.backlight();
    lcdDoorlock.setCursor(2, 0);
    lcdDoorlock.print("Entrance key:");
    lcdDoorlock.setCursor(5, 1);
    lcdDoorlock.blink();
    Serial.begin(9600);
    keypadDl.addEventListener((void (*)(char))unlock_door_event);
}
void DoorlockMainFunction()
{
    keypadDl.getKey();
    delay(10);
    if (counterDl==0)
    {
        analogWrite(doorbuzzer, 255);
    }
    else
    {
        counterDl--;
        analogWrite(doorbuzzer, 250);


    }
}
