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

    SecurityInit();
   DoorlockInit();
      ComfortInit();
}

void loop()
{

    MainFunction();
    delay(10);
}
