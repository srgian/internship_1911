#ifndef HWINPUTS_H
#define HWINPUTS_H

#include <inttypes.h>
#include "Arduino.h"
#include "Servo.h"
#include "Keypad.h"
#include "Menu.h"
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

extern uint8_t lock;
extern uint8_t pirState;
extern uint8_t val;
extern uint16_t counter;
extern uint16_t counterDl;
extern bool motionStatus;
extern size_t pospass;
extern char *parole;
extern int desiredTemperature , fahrenheitTemperature, newTemp ;
extern uint8_t alarmasts;

extern uint8_t valueMQ135;

//temperature variable


extern uint16_t buttonState, buttonLastState; //joystick button states

extern uint8_t readHumiditySoil, humidityPercentSoil;

extern uint8_t motionDetectorValue;//motion detector value



extern uint8_t statusWifi;

uint8_t SWDigitalRead(uint8_t pin);
uint8_t HWDigitalRead(uint8_t pin);

void SWReadInputs(uint8_t *dst);
void HWReadInputs(uint8_t *dst);

void SWReadDHT(double *temp, double *humid);
void HWReadDHT(double *temp, double *humid);


void RefreshListaParole();
void keypadEvent(KeypadEvent eKey);
void motion_detection();
void armed();
void disarmed();
void unlock_door_event(KeypadEvent eKey);
void lcdRefresh();

extern Keypad keypad;
extern Keypad keypadDl;

extern MENU air_quality;
extern MENU alcohol_lvl;
extern MENU current_temp;
extern MENU new_temp;
extern MENU air_humidity;
extern MENU soil_state;
extern MENU *currentMenu;

extern byte topUpDown[];



extern void infoPgSecurity();
extern int connectToWifi();

extern Servo myservo;

extern byte topUpDown[];
extern byte bottomUpDown[];
extern byte middleUpDown[];
extern byte rightArrow[];
extern byte leftArrow[];
extern byte almostHalf[];
extern byte almostFull[];
extern byte rightBlank[];
extern byte newChar1[];

#endif // HWINPUTS_H
