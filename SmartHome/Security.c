#include "Security.h"
#include "Outputs.h"
#include "Inputs.h"
uint8_t buzzer=10;

void SecurityInit()
{
    HWDigitalMode(buzzer,OUTPUT);
    HWDigitalWrite(buzzer, HIGH);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(1, 0);
    lcd.print("Enter code:");
    lcd.setCursor(0, 1);
    Serial.begin(9600);
    keypad.addEventListener((void (*)(char))keypadEvent);
}

void SecurityMainFunction()
{
    keypad.getKey();



}



