#ifndef HWINPUTS_H
#define HWINPUTS_H

#include <inttypes.h>
#include <stdint.h>

#ifndef WIN
#define ReadInputs HWReadInputs
#define digitalPinRead HWDigitalRead
#define ReadDHT HWReadDHT
//add MQ4, MQ135
#define ReadMQ4 HWReadMQ4
#define ReadMQ135 HWReadMQ135

#else
#define ReadInputs SWReadInputs
#define digitalPinRead SWDigitalRead
#define ReadDHT SWReadDHT

//add MQ4, MQ135
#define ReadMQ4 SWReadMQ4
#define ReadMQ135 SWReadMQ135

#endif // WIN

uint8_t SWDigitalRead(uint8_t pin);
uint8_t HWDigitalRead(uint8_t pin);

void SWReadInputs(uint8_t *dst);
void HWReadInputs(uint8_t *dst);

void SWReadDHT(double *temp, double *humid);
void HWReadDHT(double *temp, double *humid);

void SWReadMQ4(uint8_t *valueMQ4);
void HWReadMQ4(uint8_t *valueMQ4);

void SWReadMQ135(uint8_t *valueMQ135);
void HWReadMQ135(uint8_t *valueMQ135);

#endif // HWINPUTS_H
