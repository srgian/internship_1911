#include <Arduino.h>
#include "Logic.h"

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    MainFunction();
    delay(500);
}
