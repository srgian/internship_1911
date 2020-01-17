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
#define joyButton 2
#define joyPinY A0
#define joyPinX A1
#define soilHumidity A7
#define infraRedPin 3 //motion detector sensor

//Define Joystick keys
#define JOYSTICK_UP       B00000001 //DEC 1
#define JOYSTICK_DOWN     B00000010 //DEC 2
#define JOYSTICK_LEFT     B00000100 //DEC 4
#define JOYSTICK_RIGHT    B00001000 //DEC 8

//temperature
#define dhtPin A2
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
uint8_t alarmasts;
int desiredTemperature = 25, fahrenheitTemperature, newTemp = 20;
uint8_t valueMQ135;
uint16_t buttonState, buttonLastState; //joystick button states
uint8_t readHumiditySoil, humidityPercentSoil;
uint8_t motionDetectorValue = 0; //motion detector value
uint8_t k=0;
float alcoholValue;
dht DHT;
LiquidCrystal_I2C lcdSecurity(0x26, 20, 4);
LiquidCrystal_I2C lcdDoorlock(0x27, 20, 4);
LiquidCrystal_I2C lcdComfort(0x25, 20, 4);

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


//arrows
byte topUpDown[] =
{
    B11111,
    B00100,
    B01110,
    B11111,
    B00100,
    B11111,
    B01110,
    B00100
};

byte bottomUpDown[] =
{
    B00100,
    B01110,
    B11111,
    B00100,
    B11111,
    B01110,
    B00100,
    B11111
};

byte middleUpDown[] =
{
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100
};

byte rightArrow[] =
{
    B10000,
    B11000,
    B11100,
    B11110,
    B11110,
    B11100,
    B11000,
    B10000
};

byte leftArrow[] =
{
    B00001,
    B00011,
    B00111,
    B01111,
    B01111,
    B00111,
    B00011,
    B00001
};

byte almostHalf[] =
{
    B11111,
    B11111,
    B10001,
    B10001,
    B10001,
    B10001,
    B11111,
    B11111
};

byte almostFull[] =
{
    B11111,
    B11111,
    B11111,
    B10001,
    B10001,
    B11111,
    B11111,
    B11111
};

byte rightBlank[] =
{
    B10000,
    B11000,
    B10100,
    B10010,
    B10010,
    B10100,
    B11000,
    B10000
};
byte newChar1[]=
{
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};




//all menus declarations
MENU air_quality;
MENU alcohol_lvl;
MENU current_temp;
MENU new_temp;
MENU air_humidity;
MENU soil_state;
MENU *currentMenu = &air_quality;




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

void lcdRefresh()
{
    int pinX = analogRead(joyPinX);
    int pinY = analogRead(joyPinY);
    unsigned char joystick = 0;

    //lcd.setBacklight(HIGH);
    buttonState = digitalRead(joyButton);

    //create arrows





    //start the menu...
    lcdComfort.setCursor(2, 0);
    lcdComfort.print(currentMenu->title);

    lcdComfort.setCursor(0, 1);
    lcdComfort.print(currentMenu->prefix);
    lcdComfort.print(currentMenu->sensorValue);
    lcdComfort.print(currentMenu->suffix);

    if (currentMenu->title == "Air quality:    ")
    {
        //topUpDown arrows

        lcdComfort.setCursor(0, 0);
        lcdComfort.print((char)0);

        //rightArrow
        lcdComfort.setCursor(1, 0);
        lcdComfort.print((char)3);
    }

    if (currentMenu->title == "Temperature    ")
    {
        //middleUpDown arrows
        lcdComfort.setCursor(0, 0);
        lcdComfort.print((char)2);

        //rightArrow
        lcdComfort.setCursor(1, 0);
        lcdComfort.print((char)3);

        //press on joystick button to transform from Celsius to Fahrenheit (poor implementation - hidden feature)
        if ((buttonState == LOW) && (buttonLastState == HIGH))
        {
            Serial.println("Button pressed");
            current_temp.suffix = "F";
            DHT.temperature = DHT.temperature * 1.8 + 32;
            current_temp.sensorValue = DHT.temperature;
        }
        else if ((buttonState == HIGH) && (buttonLastState == LOW))
        {
            Serial.println("Button released");
            current_temp.sensorValue = DHT.temperature;
            current_temp.suffix = "C";
        }

        buttonLastState = buttonState;
    }

    if (currentMenu->title == "Alcohol level:  ")
    {
        //blank arrows
        lcdComfort.setCursor(0, 0);
      lcdComfort.print(char(0b11111111));

        //leftArrow
        lcdComfort.setCursor(1, 0);
        lcdComfort.print((char)4);
    }

    if (currentMenu->title == "Humidity:       ")
    {
        //middleUpDown arrows
        lcdComfort.setCursor(0, 0);
        lcdComfort.print((char)2);

        //blank
        lcdComfort.setCursor(1, 0);
        lcdComfort.print((char)6);
    }

    if (currentMenu->title == "Soil state      ")
    {
        //bottomUpDown arrow
        lcdComfort.setCursor(0, 0);
        lcdComfort.print((char)1);

        //blank
        lcdComfort.setCursor(1, 0);
        lcdComfort.print((char)6);
    }

    if (currentMenu->title == "Set new temp.:  ")
    {
        //blank
        lcdComfort.setCursor(0, 0);
        if(newTemp == 9)
        {
            lcdComfort.print(" ");
        }
        else if(newTemp >= 10 && newTemp <= 12)
        {
            lcdComfort.print(char(0b00101110));

        }
        else if(newTemp >= 13 && newTemp <= 17)
        {
            lcdComfort.print(char(0b10100001));

        }
        else if(newTemp >= 18 && newTemp <= 23)
        {
            lcdComfort.print(char(0b11011011));

        }
        else if(newTemp >= 24 && newTemp <= 29)
        {
            lcdComfort.print((char)5);
        }
        else if(newTemp >= 30 && newTemp <= 36)
        {
            lcdComfort.print((char)7);
        }
        else if(newTemp == 37)
        {
            lcdComfort.print(char(0b11111111));

        }

        //leftArrow
        lcdComfort.setCursor(1, 0);
        lcdComfort.print((char)4);

        //set new temperature
        //joystick UP | DOWN
        if (pinY >= 500)   //UP
        {
            joystick = joystick | JOYSTICK_UP ;

            if (newTemp == 37)
            {
                newTemp = 37;
            }
            else
            {
                newTemp += 1;
            }
        }
        else if (pinY <= 330)   //DOWN
        {
            joystick = joystick | JOYSTICK_DOWN ;

            if (newTemp == 9)
            {
                newTemp = 9;
            }
            else
            {
                newTemp -= 1;
            }
        }
    }
}





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


    for (int k = 0; k < cnt; k++)
    {
        char cp[5] = {};
        cp[4] = 0x00;
        memcpy(&cp, (pwd + k * 4), 4);
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
        if (lock == false)
        {
            counterDl=200;
            myservo.write(5);//unlock the door
            lcdDoorlock.clear();
            lcdDoorlock.blink_off();
            lcdDoorlock.cursor_off();
            lcdDoorlock.setCursor(2, 0);
            lcdDoorlock.print("Welcome Home!");
            delay(1000);
            lcdDoorlock.clear();
            //lcdDoorlock.noBacklight();
            lock = true;//after 5s it is locking again

        }
        lock=false;
        lcdDoorlock.clear();
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
void open_all_thetime()
{
    myservo.write(5);//unlock the door
    lcdDoorlock.clear();
    lcdDoorlock.blink_off();
    lcdDoorlock.cursor_off();
    lcdDoorlock.setCursor(2, 0);
    lcdDoorlock.print("Welcome Home!");
    delay(1000);
    lcdDoorlock.clear();
    lcdDoorlock.setCursor(6, 0);
    lcdDoorlock.print("Open!");
}

void closed()
{
    myservo.write(5);//unlock the door
    lcdDoorlock.clear();
    lcdDoorlock.blink_off();
    lcdDoorlock.cursor_off();
    lcdDoorlock.setCursor(2, 0);
    lcdDoorlock.print("It's closed!");
    delay(1000);
    lcdDoorlock.clear();
    DoorlockInit();
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
        keypressed[k] = eKey;
        k++;
    }
    Serial.println(keypressed);
    break;
    case '*':
        k = 0;
        keypressed[4] = '\0';
        if(checkpassworddl())
            keypressed[i]= {0};
        delay(500);
        k = 0;
        keypressed[4] = '\0';
        DoorlockInit();
        break;

    case '#':
        k = 0;
        keypressed[4] = '\0';
        keypressed[i]= {0};
        checkpassworddl();
        open_all_thetime();
        keypressed[i]= {0};
        delay(500);
        DoorlockInit();
        break;

    case 'C':
        k = 0;
        keypressed[4] = '\0';
        keypressed[i]= {0};
        checkpassworddl();
        closed();
        break;

    case 'A':
        DoorlockInit();
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
    alarmasts=0;
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
    alarmasts=1;
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
        keypressed[i]= {0};
        break;

    case '*':
        i = 0;
        keypressed[4] = '\0';
        if(checkpassword())
            disarmed();
        keypressed[i]= {0};
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




#endif // WIN
