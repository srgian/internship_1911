#include <inttypes.h>
#include <stdio.h>

void SWReadInputs(uint8_t *dst)
{
    *dst^=0xff;
}

uint8_t SWDigitalRead(uint8_t pin)
{
    uint8_t val=0;
    printf("Pin (%d) read value is <0x%02X>\n", pin, val);
    return val;
}

//humidity & temperature
void SWReadDHT(double *temp, double *humid)
{
    *temp=25;
    *humid=50;
}

//MQ4, MQ135
void SWReadMQ135(uint8_t *valueMQ135)
{
    *valueMQ135=225;
}
void SWReadMQ4(uint8_t *valueMQ4)
{
    *valueMQ4=80;
}
