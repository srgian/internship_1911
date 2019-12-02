#include <inttypes.h>
#ifndef WIN
#include <Arduino.h>
#define dht_apin A0 // Analog Pin 0
#include <dht.h>

dht DHT;
//uint8_t valueMQ135, valueMQ4;

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

//add MQ4, MQ135
uint8_t HWReadMQ4(uint8_t pinMQ4)
{
    uint8_t val=digitalRead(pinMQ4);
    Serial.println(pinMQ4);
    Serial.println(val);
    Serial.println("===");
    return val;
}

uint8_t HWReadMQ135(uint8_t pinMQ135)
{
    uint8_t val=digitalRead(pinMQ135);
    Serial.println(pinMQ135);
    Serial.println(val);
    Serial.println("===");
    return val;
}

#endif // WIN
