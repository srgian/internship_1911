#ifndef HWINPUTS_H
#define HWINPUTS_H

#include <inttypes.h>

#ifndef WIN
#define ReadInputs HWReadInputs
#define digitalPinRead HWDigitalRead
#define ReadDHT HWReadDHT
#else
#define ReadInputs SWReadInputs
#define digitalPinRead SWDigitalRead
#define ReadDHT SWReadDHT
#endif // WIN

uint8_t SWDigitalRead(uint8_t pin);
uint8_t HWDigitalRead(uint8_t pin);

void SWReadInputs(uint8_t *dst);
void HWReadInputs(uint8_t *dst);

void SWReadDHT(double *temp, double *humid);
void HWReadDHT(double *temp, double *humid);

#endif // HWINPUTS_H
