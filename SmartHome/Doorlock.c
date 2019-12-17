#include "Doorlock.h"
#include "Outputs.h"
#include "Inputs.h"

uint8_t doorbuzzer = 12;
uint8_t lock;


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
    keypad.addEventListener((void (*)(char))unlock_door_event);
}
void DoorlockMainFunction()
{
  keypad.getKey();
}
