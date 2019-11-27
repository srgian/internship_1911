#include <inttypes.h>
#ifndef WIN
#include <Arduino.h>
#define dht_apin A0 // Analog Pin 0
#include <dht.h>

dht DHT;

void HWReadInputs(uint8_t *dst)
{
    *dst^=0xff;
}

uint8_t HWDigitalRead(uint8_t pin)
{
    uint8_t val=digitalRead(pin);
    Serial.println(pin);
    Serial.println(val);
    Serial.println("===");
    return val;
}

void HWReadDHT(double *temp, double *humid)
{
    DHT.read11(dht_apin);
    *temp=DHT.temperature;
    *humid=DHT.humidity;
}

#endif // WIN
