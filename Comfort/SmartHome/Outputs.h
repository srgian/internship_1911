#ifndef HWOUTPUTS_H
#define HWOUTPUTS_H

#ifndef WIN
#include <Arduino.h>
#define Print HWPrint
#define DPrint HWDPrint
#define digitalPinWrite HWDigitalWrite
#define digitalPinMode HWDigitalMode
#define WriteOutputs HWWriteOutputs
#else
#define Print SWPrint
#define DPrint SWDPrint
#define digitalPinWrite SWDigitalWrite
#define digitalPinMode SWDigitalMode
#define WriteOutputs SWWriteOutputs
#endif // WIN

#include <inttypes.h>

void HWDigitalWrite(uint8_t pin, uint8_t val);
void HWDigitalMode(uint8_t pin, uint8_t val);

void SWDigitalWrite(uint8_t pin, uint8_t val);
void SWDigitalMode(uint8_t pin, uint8_t val);

void HWWriteOutputs(uint8_t *val);
void SWWriteOutputs(uint8_t *val);

void HWPrint(char *str);
void SWPrint(char *str);

void HWDPrint(double val);
void SWDPrint(double val);

#endif // HWOUTPUTS_H