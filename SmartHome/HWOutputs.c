#include <inttypes.h>
#ifndef WIN
#include <Arduino.h>

void HWWriteOutputs(uint8_t *val)
{
    Serial.println(*val);
}

void HWDigitalMode(uint8_t pin, uint8_t mode)
{
    pinMode(pin, mode);
}

void HWDigitalWrite(uint8_t pin, uint8_t val)
{
    digitalWrite(pin, val);
}
#endif // WIN
