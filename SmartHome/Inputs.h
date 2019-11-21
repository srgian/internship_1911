#ifndef HWINPUTS_H
#define HWINPUTS_H

#include <inttypes.h>

#ifndef WIN
#define ReadInputs HWReadInputs
#else
#define ReadInputs SWReadInputs
#endif // WIN

void SWReadInputs(uint8_t *dst);
void HWReadInputs(uint8_t *dst);

#endif // HWINPUTS_H
