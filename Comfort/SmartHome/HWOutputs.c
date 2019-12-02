#include <inttypes.h>
#ifndef WIN
#include <Arduino.h>

void HWPrint(char *str)
{
    Serial.println(str);
}

//MQ4
void HWPrintMQ4(char *strMQ4)
{
    Serial.println(strMQ4);
}


void HWPrintMQ135(char *strMQ135)
{
    Serial.println(strMQ135);
}

void HWDPrint(double val)
{
    Serial.println(val);
}

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
