#include <inttypes.h>

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

void SWReadDHT(double *temp, double *humid)
{
    *temp=25;
    *humid=50;
}
