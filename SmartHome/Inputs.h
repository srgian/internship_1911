#ifndef HWINPUTS_H
#define HWINPUTS_H

#include <inttypes.h>

#ifndef WIN
#define ReadInputs HWReadInputs
#define digitalPinRead HWDigitalRead
#else
#define ReadInputs SWReadInputs

#endif // WIN
uint8_t HWDigitalRead(uint8_t pin);

void SWReadInputs(uint8_t *dst);
void HWReadInputs(uint8_t *dst);

#endif // HWINPUTS_H
