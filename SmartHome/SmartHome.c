#include <Arduino.h>
#include "Logic.h"
#include "Lights.h"


void setup()
{
    Serial.begin(9600);
    LightsInit();
}

void loop()
{

    MainFunction();
    delay(500);
}
