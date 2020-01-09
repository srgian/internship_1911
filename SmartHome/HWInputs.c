#include <inttypes.h>
#include <Servo.h>
#ifndef WIN
#include <Arduino.h>
#define dht_apin A0 // Analog Pin 0
#include <dht.h>
#include "Keypad.h"
#include "Inputs.h"
#include "Password.h"
#include "LiquidCrystal_I2C.h"
#include "Doorlock.h"
#include "WifiConn.h"
#define ROWS 4
#define COLS 4
#define inputPin 11
#define buzzer 10
#define doorbuzzer 12
char keypressed[5];
char* pwd;//="2574364888374175";
int cnt =4;
int i = 0;
bool passwordvalid;
uint8_t lock;
uint8_t pirState = LOW;
uint8_t val = 0;
bool motionStatus;
uint16_t counterDl=0;
char cp;
Servo myservo;
LiquidCrystal_I2C lcdSecurity(0x27, 20, 4);
LiquidCrystal_I2C lcdDoorlock(0x26, 20, 4);

Password doorpassword = Password( "1234" );
//Password password= ( char*)cp;

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

/*void enter_house()
{

        //statuspwd = true;
        lcdDoorlock.clear();
        lcdDoorlock.blink_off();
        lcdDoorlock.cursor_off();
        lcdDoorlock.setCursor(4, 0);
        lcdDoorlock.print("Success!");
        delay(500);
        if (lock == false)
        {
            counterDl=500;
            myservo.write(5);//unlock the door

            lcdDoorlock.clear();
            lcdDoorlock.setCursor(2, 0);
            lcdDoorlock.print("Welcome home!");
            delay(500);

            lock = true;//after 5s it is locking again
        }
        lcdDoorlock.clear();
        lcdDoorlock.noBacklight();

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
    }*/


static int j;
int passwordevaluate(char cp[])
{
    passwordvalid = true;
    int retval = 0;
    Serial.println(keypressed);
    Serial.println(cp);
    retval = strcmp(keypressed, cp);
    if ( retval != 0)
    {
        passwordvalid = false;
    }
    return retval;

}
int checkpassword()
{

    if(statusWifi == 0)
    {
        connToWifi();
    }
    if(pwd == NULL)
    {
        infoPgSecurity();
        pwd=parole;
    }

    Serial.println(pwd);
    int allgood = 0;


    for (int i = 0; i < cnt; i++)
    {
        char cp[5] = {};
        cp[4] = 0x00;
        memcpy(&cp, (pwd + i * 4), 4);
        passwordevaluate(cp);
        if (passwordvalid)
        {
            allgood = 1;
        }

    }

    Serial.print("all good=");
    Serial.println(allgood);
    if (allgood)

    {
        lcdSecurity.backlight();
        lcdSecurity.clear();
        lcdSecurity.print("Succes!");
        lock = false;
        delay(100);
    }
    else
    {

        lcdSecurity.clear();
        lcdSecurity.print("Try again!");
        delay(100);
        lcdSecurity.clear();
        lcdSecurity.print("Enter code:");
        lcdSecurity.setCursor(0, 1);
        lock = true;
    }

    return allgood;

}
int checkpassworddl()
{

    if(statusWifi == 0)
    {
        connToWifi();
    }
    if(pwd == NULL)
    {
        infoPgSecurity();
        pwd=parole;
    }

    Serial.println(pwd);
    int good = 0;


    for (int i = 0; i < cnt; i++)
    {
        char cp[5] = {};
        cp[4] = 0x00;
        memcpy(&cp, (pwd + i * 4), 4);
        passwordevaluate(cp);
        if (passwordvalid)
        {
            good = 1;
        }

    }

    Serial.print("all good=1");
//    Serial.println(allgood);
    if (good)

    {
        lcdDoorlock.clear();
        lcdDoorlock.blink_off();
        lcdDoorlock.cursor_off();
        lcdDoorlock.setCursor(4, 0);
        lcdDoorlock.print("Success!");
        delay(500);
        if (lock == false)
        {
            counterDl=500;
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
    return good;

}

void unlock_door_event(KeypadEvent eKey)
{
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
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':

    {
        keypressed[i] = eKey;
        i++;
    }
    Serial.println(keypressed);
    break;
    case '*':
        i = 0;
        keypressed[4] = '\0';
        if(checkpassworddl())
            break;

    case 'C':
        Serial.println("Clear");
        i = 0;
        lcdDoorlock.clear();
        lcdDoorlock.backlight();
        lcdDoorlock.setCursor(2, 0);
        lcdDoorlock.print("Entrance key:");
        lcdDoorlock.setCursor(5, 1);
        break;
    default:
        break;
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
    lcdSecurity.clear();
    lcdSecurity.setCursor(0,1 );
    lcdSecurity.print("Sistem Disarmed");
    delay(2000);
    analogWrite(buzzer, 255);
    pirState = HIGH;
    lcdSecurity.noBacklight();
}
void armed()
{
    lcdSecurity.clear();
    lcdSecurity.setCursor(0, 1);
    lcdSecurity.print("Sistem Armed");
    delay(2000);
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
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':

    {
        keypressed[i] = eKey;
        i++;
    }
    Serial.println(keypressed);
    break;
    case '#':
        i = 0;
        keypressed[4] = '\0';
        if(checkpassword())
            armed();
    case '*':
        i = 0;
        keypressed[4] = '\0';
        if(checkpassword())
            disarmed();
        break;
    case 'C':
        Serial.println("clear");
        i = 0;
        lcdSecurity.clear();
        lcdSecurity.backlight();
        lcdSecurity.print("Enter code:");
        lcdSecurity.setCursor(0, 1);
        break;
    default:
        break;
    }
    }

}


/*void RefreshListaParole()
{

    infoPgSecurity();

    Serial.println("Mai departe");
    pwd=parole;
    int cnt=pospass/4;
    Serial.println(pwd);
    Serial.println(cnt);

}*/


#endif // WIN
