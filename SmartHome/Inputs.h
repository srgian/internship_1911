#ifndef HWINPUTS_H
#define HWINPUTS_H

#include <inttypes.h>
#include "Arduino.h"
#include "Servo.h"
#include "Keypad.h"
//#include "Servo.h"
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
extern uint16_t counter;
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
void unlock_door_event(KeypadEvent eKey);

extern Keypad keypad;
extern Keypad keypadDl;


extern Servo myservo;

#endif // HWINPUTS_H
