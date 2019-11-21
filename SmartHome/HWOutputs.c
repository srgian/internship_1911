#include <inttypes.h>
#ifndef WIN
#include <Arduino.h>

void HWWriteOutputs(uint8_t *val)
{
    Serial.println(*val);
}

#endif // WIN
