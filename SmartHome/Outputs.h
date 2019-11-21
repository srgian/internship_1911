#ifndef HWOUTPUTS_H
#define HWOUTPUTS_H

#ifndef WIN
#include <Arduino.h>
#define WriteOutputs HWWriteOutputs
#else
#define WriteOutputs SWWriteOutputs
#endif // WIN

#include <inttypes.h>

void HWWriteOutputs(uint8_t *val);
void SWWriteOutputs(uint8_t *val);

#endif // HWOUTPUTS_H
