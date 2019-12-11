#include "Security.h"
#include "Outputs.h"
#include "Inputs.h"
uint8_t inputPin=11;
uint8_t buzzer=10;

void SecurityInit()
{
    HWDigitalMode(buzzer,OUTPUT);
    HWDigitalWrite(buzzer, HIGH);
    HWDigitalMode(pirState,INPUT);

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

 motion_detection();
  keypad.getKey();
  delay(10);
  if (motionStatus == true) {
    if (counter == 0)
    { analogWrite(buzzer, 250);
      counter = 1500;
      Serial.println("15s");
    } else {
      counter--;
    }
  }
}



