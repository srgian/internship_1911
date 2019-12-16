#include "Doorlock.h"
#include "Outputs.h"
#include "Inputs.h"

uint8_t doorbuzzer = 10;
uint8_t lock;


void DoorlockInit()
{
    HWDigitalMode(doorbuzzer,OUTPUT);
    HWDigitalWrite(doorbuzzer, HIGH);
    //myservo.attach(9);// attaching to the 9th pin
    analogWrite(doorbuzzer, 255);


    lcd.init();
    lcd.backlight();
    lcd.setCursor(2, 0);
    lcd.print("Entrance key:");
    lcd.setCursor(5, 1);
    lcd.blink();
    Serial.begin(9600);
    keypad.addEventListener((void (*)(char))unlock_door_event);
}
void DoorlockMainFunction()
{
  keypad.getKey();
}
