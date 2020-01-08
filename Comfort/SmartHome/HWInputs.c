#include <inttypes.h>
#include <Servo.h>
#ifndef WIN
#include <Arduino.h>
#define dht_apin A0 // Analog Pin 0
#include <dht.h>
#include "Keypad.h"
#include "Password.h"
#include "LiquidCrystal_I2C.h"
#include "Doorlock.h"
#define ROWS 4
#define COLS 4
#define inputPin 11
#define buzzer 10
#define doorbuzzer 12
uint8_t lock;
uint8_t pirState = LOW;
uint8_t val = 0;
bool motionStatus;
uint16_t counterDl=0;
Servo myservo;
LiquidCrystal_I2C lcdSecurity(0x27, 20, 4);
LiquidCrystal_I2C lcdDoorlock(0x26, 20, 4);

Password doorpassword = Password( "1234" );
Password password = Password( "1564" );

bool statuspwd;

char hexaKeysDoorlock[ROWS][COLS] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPinsDl[ROWS] = {52, 50, 48, 46};
byte colPinsDl[COLS] = {53, 51, 49, 47};
Keypad keypadDl = Keypad(makeKeymap(hexaKeysDoorlock), rowPinsDl, colPinsDl, ROWS, COLS);

char hexaKeys[ROWS][COLS] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

dht DHT;


void HWReadInputs(uint8_t *dst)
{
    *dst^=0xff;
}

uint8_t HWDigitalRead(uint8_t pin)
{
    uint8_t val=digitalRead(pin);
    Serial.println(pin);
    Serial.println(val);
    Serial.println("===");
    return val;
}

void HWReadDHT(double *temp, double *humid)
{
    DHT.read11(dht_apin);
    *temp=DHT.temperature;
    *humid=DHT.humidity;
}

void enter_house()
{
    if (doorpassword.evaluate())
    {
        statuspwd = true;
        lcdDoorlock.clear();
        lcdDoorlock.blink_off();
        lcdDoorlock.cursor_off();
        lcdDoorlock.setCursor(4, 0);
        lcdDoorlock.print("Success!");
        delay(500);
        if (lock == false)
        {   counterDl=500;
            myservo.write(5);//unlock the door

            lcdDoorlock.clear();
            lcdDoorlock.setCursor(2, 0);
            lcdDoorlock.print("Welcome home!");
            delay(500);

            lock = true;//after 5s it is locking again
        }
        lcdDoorlock.clear();
        lcdDoorlock.noBacklight();
    }
    else
    {
        statuspwd = false;
        counterDl=0;
        lcdDoorlock.clear();
        lcdDoorlock.blink_off();
        lcdDoorlock.cursor_off();
        lcdDoorlock.setCursor(4, 0);
        lcdDoorlock.print("Wrong!");
        analogWrite(doorbuzzer, 250);
        delay(1000);
        lcdDoorlock.clear();
        lcdDoorlock.blink();
        lcdDoorlock.setCursor(2, 0);
        lcdDoorlock.print("Entrance key:");
        lcdDoorlock.setCursor(5, 1);
    }
}

void checkPassword()
{
     if (password.evaluate())
    {
        digitalWrite(buzzer, HIGH);
        lcdSecurity.clear();
        lcdSecurity.blink_off();
        lcdSecurity.cursor_off();
        lcdSecurity.print("Success");
        delay(1000);
        pirState = HIGH;
        digitalWrite(buzzer, HIGH);
        lcdSecurity.clear();
        lcdSecurity.noBacklight();
        //iseval=true;
    }
    else
    {
        lcdSecurity.backlight();
        analogWrite(buzzer, 250);
        lcdSecurity.clear();
        lcdSecurity.blink_off();
        lcdSecurity.cursor_off();
        lcdSecurity.print("Wrong");
        delay(1000);
        analogWrite(pirState, 0);// read input value
        lcdSecurity.clear();
        lcdSecurity.backlight();
        lcdSecurity.print("Enter code:");
        lcdSecurity.setCursor(0, 1);
       // iseval=false;
    }

}
void unlock_door_event(KeypadEvent eKey) {
  switch (keypadDl.getState())
  {

    case PRESSED:
      {
        lcdDoorlock.blink_on();
        lcdDoorlock.cursor_on();
        lcdDoorlock.print("*");
        Serial.println(eKey);
      }
      switch (eKey)
      {
        case '*':
          enter_house();
          doorpassword.reset();
          break;
        case 'A':
          lcdDoorlock.clear();
          lcdDoorlock.backlight();
          lcdDoorlock.setCursor(2, 0);
          lcdDoorlock.print("Entrance key:");
          lcdDoorlock.setCursor(5, 1);
          break;
        default:
          doorpassword.append(eKey);
      }
  }

}
void motion_detection()
{

    val = digitalRead(inputPin);  // read input value
    if (val == HIGH)              // check if the input is HIGH
    {

        if (pirState == LOW)
        {
            // we have just turned on
            Serial.println("Motion detected!");
            motionStatus = true;
            pirState = HIGH;
        }
    }
}

void disarmed()
{

    if (password.evaluate())
    {
        lcdSecurity.backlight();
        lcdSecurity.clear();
        lcdSecurity.setCursor(1, 0);
        lcdSecurity.print("Sistem Disarmed");
        delay(2000);
        lcdSecurity.noBacklight();
    }
    pirState = HIGH;

    lcdSecurity.noBacklight();
}
void armed()
{

      if (password.evaluate())
    {
        lcdSecurity.backlight();
        lcdSecurity.clear();
        lcdSecurity.setCursor(1, 0);
        lcdSecurity.print("System Armed");

    }
    delay(10000);
    pirState = LOW;

    lcdSecurity.noBacklight();
}
void keypadEvent(KeypadEvent eKey)
{
    switch (keypad.getState())
    {
    case PRESSED:
    {
        lcdSecurity.blink_on();
        lcdSecurity.cursor_on();
        lcdSecurity.print("*");
        Serial.println(eKey);
    }
    switch (eKey)
    {
    case '#':
        checkPassword();
        armed();
        password.reset();
        break;
    case '*':
        checkPassword();
        disarmed();
        password.reset();
        motionStatus = false;
        break;
    case 'C':
        lcdSecurity.clear();
        lcdSecurity.backlight();
        password.reset();
        lcdSecurity.print("Enter code:");
        lcdSecurity.setCursor(0, 1);
        break;
    default:
        password.append(eKey);

    }
    }
}




/*void RefreshListaParole(pwd,nr_parole)
{
    wifi: bizkit.eu/~arobs-i1911/cfg/security.php
*/


#endif // WIN
