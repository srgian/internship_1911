#include <inttypes.h>
#include <stdio.h>

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
