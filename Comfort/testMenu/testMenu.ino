#include "dht.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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

LiquidCrystal_I2C lcd(0x27, 20, 4); //lcd object

int desiredTemperature = 25, fahrenheitTemperature, newTemp = 22;

int valueMQ135;

//temperature variable
dht DHT;

int buttonState, buttonLastState; //joystick button states

int readHumiditySoil, humidityPercentSoil;

int motionDetectorValue = 0; //motion detector value

float alcoholValue;

//arrows

byte topUpDown[] = {
  B11111,
  B00100,
  B01110,
  B11111,
  B00100,
  B11111,
  B01110,
  B00100
};

byte bottomUpDown[] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B11111,
  B01110,
  B00100,
  B11111
};

byte middleUpDown[] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};

byte rightArrow[] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11110,
  B11100,
  B11000,
  B10000
};

byte leftArrow[] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B01111,
  B00111,
  B00011,
  B00001
};

byte nullArrow[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte leftBlank[] = {
  B00001,
  B00011,
  B00101,
  B01001,
  B01001,
  B00101,
  B00011,
  B00001
};

byte rightBlank[] = {
  B10000,
  B11000,
  B10100,
  B10010,
  B10010,
  B10100,
  B11000,
  B10000
};

//define MENU struct
typedef struct MENU MENU;
struct MENU {
  MENU *prevMenu;
  MENU *nextMenu;
  MENU *subMenu;
  MENU *parent;
  int sensorValue;
  char *title;
  char *prefix;
  char *suffix;
  bool writable;
};

//all menus declarations
MENU air_quality;
MENU alcohol_lvl;
MENU current_temp;
MENU new_temp;
MENU air_humidity;
MENU soil_state;
MENU *currentMenu = &air_quality;

void lcdRefresh()
{
  int pinX = analogRead(joyPinX);
  int pinY = analogRead(joyPinY);
  unsigned char joystick = 0;

  //lcd.setBacklight(HIGH);
  buttonState = digitalRead(joyButton);

  //create arrows
  lcd.createChar(0, topUpDown);
  lcd.createChar(1, bottomUpDown);
  lcd.createChar(2, middleUpDown);
  lcd.createChar(3, rightArrow);
  lcd.createChar(4, leftArrow);
  lcd.createChar(5, nullArrow);
  lcd.createChar(6, rightBlank);
  lcd.createChar(7, leftBlank);

  //start the menu...
  lcd.setCursor(2, 0);
  lcd.print(currentMenu->title);

  lcd.setCursor(0, 1);
  lcd.print(currentMenu->prefix);
  lcd.print(currentMenu->sensorValue);
  lcd.print(currentMenu->suffix);

  if (currentMenu->title == "Air quality:    ") {
    //topUpDown arrows
    lcd.setCursor(0, 0);
    lcd.print(char(0));

    //rightArrow
    lcd.setCursor(1, 0);
    lcd.print(char(3));

    lcd.noBlink();
  }

  if (currentMenu->title == "Temperature    ") {
    //middleUpDown arrows
    lcd.setCursor(0, 0);
    lcd.print(char(2));

    //rightArrow
    lcd.setCursor(1, 0);
    lcd.print(char(3));


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
      //DHT.temperature = DHT.temperature;
      current_temp.suffix = "C";
    }

    buttonLastState = buttonState;

    lcd.noBlink();
  }

  if (currentMenu->title == "Alcohol level:  ") {
    //blank arrows
    lcd.setCursor(0, 0);
    lcd.print(char(5));

    //leftArrow
    lcd.setCursor(1, 0);
    lcd.print(char(4));

    lcd.noBlink();
  }

  if (currentMenu->title == "Humidity:       ") {
    //middleUpDown arrows
    lcd.setCursor(0, 0);
    lcd.print(char(2));

    //blank
    lcd.setCursor(1, 0);
    lcd.print(char(6));

    lcd.noBlink();
  }

  if (currentMenu->title == "Soil state      ") {
    //bottomUpDown arrow
    lcd.setCursor(0, 0);
    lcd.print(char(1));

    //blank
    lcd.setCursor(1, 0);
    lcd.print(char(6));

    lcd.noBlink();
  }

  if (currentMenu->title == "Set new temp.:  ") {
    //blank
    lcd.setCursor(0, 0);
    lcd.print(char(5));

    //leftArrow
    lcd.setCursor(1, 0);
    lcd.print(char(4));

    //set new temperature
    //joystick UP | DOWN
    if (pinY >= 450) { //UP
      joystick = joystick | JOYSTICK_UP ;

      if (newTemp == 37) {
        newTemp = 37;
      } 
      else {
        newTemp += 1;
      }

    }
    else if (pinY <= 350) { //DOWN
      joystick = joystick | JOYSTICK_DOWN ;

      if (newTemp == 9) {
        newTemp = 9;
      }
      else {
        newTemp -= 1;

      }
    }
  }
}

void setup() {

  //menu for air_quality
  air_quality.title = "Air quality:    ";
  air_quality.prevMenu = NULL;
  air_quality.subMenu = &alcohol_lvl;
  air_quality.nextMenu = &current_temp;
  air_quality.parent = NULL;
  //air_quality.prefix = ": ";
  air_quality.suffix = "ppm           ";

  //menu for alcohol_lvl (subMenu of air_quality parent)
  alcohol_lvl.title = "Alcohol level:  ";
  alcohol_lvl.prevMenu = NULL;
  alcohol_lvl.nextMenu = NULL;
  alcohol_lvl.subMenu = NULL;
  alcohol_lvl.parent = &air_quality;
  alcohol_lvl.prefix = NULL;
  alcohol_lvl.suffix = "mg/l            ";

  //menu for current_temp
  current_temp.title = "Temperature    ";
  current_temp.prevMenu = &air_quality;
  current_temp.subMenu = &new_temp;
  current_temp.parent = NULL;
  current_temp.nextMenu = &air_humidity;
  current_temp.prefix = "Current: ";
  current_temp.suffix = "C              ";

  //menu for new_temp (subMenu for current_temp)
  new_temp.title = "Set new temp.:  ";
  new_temp.prevMenu = NULL;
  new_temp.subMenu = NULL;
  new_temp.parent = &current_temp;
  new_temp.nextMenu = NULL;
  new_temp.prefix = NULL;
  new_temp.suffix = "C               ";

  //menu for air_humidity
  air_humidity.title = "Humidity:       ";
  air_humidity.prevMenu = &current_temp;
  air_humidity.subMenu = NULL;
  air_humidity.nextMenu = &soil_state;
  air_humidity.parent = NULL;
  air_humidity.prefix = NULL;
  air_humidity.suffix = "%               ";

  //menu for soil_state
  soil_state.title = "Soil state      ";
  soil_state.prevMenu = &air_humidity;
  soil_state.subMenu = NULL;
  soil_state.nextMenu = NULL;
  soil_state.parent = NULL;
  //soil_state.prefix;
  soil_state.suffix = "%               ";

  //lcd
  lcd.init();
  //lcd.setBacklight(HIGH);

  //joystick
  pinMode(joyButton, INPUT);
  digitalWrite(joyButton, HIGH);

  buttonLastState = digitalRead(joyButton);

  Serial.begin(9600);
}

void loop() {
  //joystick states
  unsigned char joystick = 0;
  static unsigned char oldJoystick = 0;

  //temp
  DHT.read11(dhtPin);

  valueMQ135 = analogRead(A3);
  alcoholValue = valueMQ135 / 100;
  //sensorValue
  air_quality.sensorValue = valueMQ135;
  alcohol_lvl.sensorValue = (float)alcoholValue;
  current_temp.sensorValue = DHT.temperature;
  new_temp.sensorValue = newTemp;
  air_humidity.sensorValue = DHT.humidity;
  soil_state.sensorValue = humidityPercentSoil;

  //set new temp.
  if (newTemp == 37) {
    new_temp.suffix = "C-maxim point!";
    //newTemp = 37;
  }
  else if (newTemp == 9) {
    //lcd.setCursor(0, 1);
    new_temp.suffix = "C-minim point!";
    newTemp = 9;

  }
  else {
    new_temp.suffix = "C                ";

  }

  //soil state
  readHumiditySoil = analogRead(soilHumidity); //read sensor value
  humidityPercentSoil = map(readHumiditySoil, 1023, 0, 0, 100); //transform data in percent
  if (soil_state.sensorValue < 10) {
    soil_state.prefix = "Wet the soil! ";
  } else if (humidityPercentSoil >= 10) {
    soil_state.prefix = "Poor value: ";
  } else if (humidityPercentSoil >= 50) {
    soil_state.prefix = "Good value: ";
  } else if (humidityPercentSoil >= 85) {
    soil_state.prefix = "Too high... ";
  }

  //alcohol value
  if (alcoholValue >= 5) {
    alcohol_lvl.prefix = "Alert! ";
  }
  else {
    alcohol_lvl.prefix = "Normal: ";
  }

  //motion detector
  motionDetectorValue = digitalRead(infraRedPin);
  if (motionDetectorValue == HIGH) {
    lcd.setBacklight(HIGH);
  }
  else {
    lcd.setBacklight(LOW);
  }

  int pinX = analogRead(joyPinX);
  int pinY = analogRead(joyPinY);

  Serial.print("X: ");
  Serial.println(pinX);
  Serial.print("Y: ");
  Serial.println(pinY);

  //joystick UP | DOWN | RIGHT | LEFT
  if (pinY >= 450) { //UP
    joystick = joystick | JOYSTICK_UP ;
  }
  else if (pinY <= 350) { //DOWN
    joystick = joystick | JOYSTICK_DOWN ;
  }
  else if (pinX >= 450) { //RIGHT
    joystick = joystick | JOYSTICK_RIGHT;
  }
  else if (pinX <= 350) { //LEFT
    joystick = joystick | JOYSTICK_LEFT;
  }

  Serial.print("Joystick value: ");
  Serial.println(joystick);

  //menu interactions
  if ((joystick == JOYSTICK_UP) && (oldJoystick == 0))
  {
    Serial.println("Joystick up");
    if (currentMenu->prevMenu != NULL)
    {
      currentMenu = currentMenu->prevMenu;
    }
  }
  else if ((joystick == JOYSTICK_DOWN) && (oldJoystick == 0))
  {
    if (currentMenu->nextMenu != NULL)
    {
      currentMenu = currentMenu->nextMenu;
    }
    Serial.println("Joystick down");
  }
  else if ((joystick == JOYSTICK_LEFT) && (oldJoystick == 0))
  {
    Serial.println("Joystick left");

    if (currentMenu->parent != NULL)
    {
      currentMenu = currentMenu->parent;
    }
  }
  else if ((joystick == JOYSTICK_RIGHT) && (oldJoystick == 0))
  {
    Serial.println("Joystick right");

    if (currentMenu->subMenu != NULL)
    {
      currentMenu = currentMenu->subMenu;
    }
  }

  oldJoystick = joystick;

  lcdRefresh();
}
