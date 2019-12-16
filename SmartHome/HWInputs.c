#include <inttypes.h>
#include <Servo.h>
#include <ServoTimers.h>
#ifndef WIN
#include <Arduino.h>
#define dht_apin A0 // Analog Pin 0
#include <dht.h>
#include "Keypad.h"
#include "Password.h"
#include "LiquidCrystal_I2C.h"
#define ROWS 4
#define COLS 4
#define buzzer 10
#define inputPin 11

uint8_t doorbuzzer = 10;
uint8_t lock;
uint8_t pirState = LOW;
uint8_t val = 0;
uint8_t counter = 1500;
bool motionStatus;
//Servo myservo;
LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd1(0x28, 20, 4);

Password doorpassword = Password( "1234" );
Password password = Password( "1564" );

bool statuspwd;

char hexaKeys[ROWS][COLS] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
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
        lcd.clear();
        lcd.blink_off();
        lcd.cursor_off();
        lcd.setCursor(4, 0);
        lcd.print("Success!");
        delay(1000);
        if (lock == false)
        {
            //myservo.write(5);//unlock the door
            analogWrite(doorbuzzer, 250);
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Welcome home!");
            delay(5000);
            analogWrite(doorbuzzer, 255);
            lock = true;//after 5s it is locking again
        }
        lcd.clear();
        lcd.noBacklight();
    }
    else
    {
        statuspwd = false;
        lcd.clear();
        lcd.blink_off();
        lcd.cursor_off();
        lcd.setCursor(4, 0);
        lcd.print("Wrong!");
        analogWrite(doorbuzzer, 250);
        delay(2000);
        analogWrite(doorbuzzer, 255);
        lcd.clear();
        lcd.blink();
        lcd.setCursor(2, 0);
        lcd.print("Entrance key:");
        lcd.setCursor(5, 1);
    }
}

void checkPassword()
{
    if (password.evaluate())
    {
        digitalWrite(buzzer, HIGH);
        lcd.clear();
        lcd.blink_off();
        lcd.cursor_off();
        lcd.print("Success");
        delay(1000);
        pirState = HIGH;
        digitalWrite(buzzer, HIGH);
        lcd.clear();
        delay(1000);
        lcd.noBacklight();
    }
    else
    {
        lcd.backlight();
        analogWrite(buzzer, 250);
        lcd.clear();
        lcd.blink_off();
        lcd.cursor_off();
        lcd.print("Wrong");
        delay(1000);
        analogWrite(pirState, 0);// read input value
        lcd.clear();
        lcd.backlight();
        lcd.print("Enter code:");
        lcd.setCursor(0, 1);
    }
}
void unlock_door_event(KeypadEvent eKey) {
  switch (keypad.getState())
  {

    case PRESSED:
      {
        lcd.blink_on();
        lcd.cursor_on();
        lcd.print("*");
        Serial.println(eKey);
      }
      switch (eKey)
      {
        case '*':
          enter_house();
          doorpassword.reset();
          break;
        case 'A':
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(2, 0);
          lcd.print("Entrance key:");
          lcd.setCursor(5, 1);
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
        lcd.backlight();
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Sistem Disarmed");
        delay(2000);
        lcd.noBacklight();
    }
    pirState = HIGH;

    lcd.noBacklight();
}
void armed()
{

    if (password.evaluate())
    {
        lcd.backlight();
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Sistem Armed");
        delay(2000);
        lcd.noBacklight();
    }
    delay(10000);
    pirState = LOW;

    lcd.noBacklight();
}
void keypadEvent(KeypadEvent eKey)
{
    switch (keypad.getState())
    {
    case PRESSED:
    {
        lcd.blink_on();
        lcd.cursor_on();
        lcd.print(eKey);
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
        lcd.clear();
        lcd.backlight();
        password.reset();
        lcd.print("Enter code:");
        lcd.setCursor(0, 1);
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
