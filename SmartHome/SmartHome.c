#include <Arduino.h>
#include "Logic.h"
#include "Lights.h"
#include "Comfort.h"
#include "Security.h"
#include "Doorlock.h"


void setup()
{
    Serial.begin(9600);
    //LightsInit();
    //ComfortInit();
    SecurityInit();
    DoorlockInit();
}

void loop()
{

    MainFunction();
    delay(10);
}
