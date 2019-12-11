#ifndef HWINPUTS_H
#define HWINPUTS_H

#include <inttypes.h>
#include "Keypad.h"
#ifndef WIN

#define ReadInputs HWReadInputs
#define digitalPinRead HWDigitalRead
#define ReadDHT HWReadDHT

#else
#define ReadInputs SWReadInputs
#define digitalPinRead SWDigitalRead
#define ReadDHT SWReadDHT
#endif // WIN

extern uint8_t pirState;
extern uint8_t val;
extern uint8_t counter;
extern bool motionStatus;

uint8_t SWDigitalRead(uint8_t pin);
uint8_t HWDigitalRead(uint8_t pin);

void SWReadInputs(uint8_t *dst);
void HWReadInputs(uint8_t *dst);

void SWReadDHT(double *temp, double *humid);
void HWReadDHT(double *temp, double *humid);


void checkPassword();
void keypadEvent(KeypadEvent eKey);
void motion_detection();
void armed();
void disarmed();

extern Keypad keypad;



#endif // HWINPUTS_H
