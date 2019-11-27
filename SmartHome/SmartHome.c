#include <Arduino.h>
#include "Logic.h"
#include "Lights.h"
#include "Comfort.h"


void setup()
{
    Serial.begin(9600);
    LightsInit();
    ComfortInit();
}

void loop()
{

    MainFunction();
    delay(500);
}
