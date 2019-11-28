#include <inttypes.h>
#include <stdio.h>

void SWPrint(char *str)
{
    printf("%s\n", str);
}

void SWDPrint(double val)
{
    printf("%f\n", val);
}

void SWDigitalWrite(uint8_t pin, uint8_t val)
{
    printf("Pin (%d) write value set to <%d>\n", pin, val);
}
void SWDigitalMode(uint8_t pin, uint8_t val)
{
    printf("Pin (%d) mode set to <%d>\n", pin, val);
}

void SWWriteOutputs(uint8_t *val)
{
    printf("%d\n", *val);
}
