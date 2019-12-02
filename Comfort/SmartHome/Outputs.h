#ifndef HWOUTPUTS_H
#define HWOUTPUTS_H

#ifndef WIN
#include <Arduino.h>
#define Print HWPrint
#define DPrint HWDPrint

//for MQ4, MQ135
#define PrintMQ4 HWPrintMQ4
#define PrintMQ135 HWPrintMQ135
#define DPrintMQ4 HWDPrintMQ4
#define DPrintMQ135 HWDPrintMQ135

#define digitalPinWrite HWDigitalWrite
#define digitalPinMode HWDigitalMode
#define WriteOutputs HWWriteOutputs

#else

#define Print SWPrint
#define DPrint SWDPrint

//for MQ4, MQ135
#define PrintMQ4 SWPrintMQ4
#define PrintMQ135 SWPrintMQ135
#define DPrintMQ4 SWDPrintMQ4
#define DPrintMQ135 SWDPrintMQ4

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

//for MQ4, MQ135
//void HWPrintMQ4(char *strMQ4);
//void SWPrintMQ135(char *strMQ135);

void HWDPrintMQ135(uint8_t *valueMQ135);
void SWDPrintMQ135(uint8_t *valueMQ135);

void HWDPrintMQ4(uint8_t *valueMQ4);
void SWDPrintMQ4(uint8_t *valueMQ4);

#endif // HWOUTPUTS_H
