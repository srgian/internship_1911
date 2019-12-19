#include "dht.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define joyButton 2
#define joyPinX A0
#define joyPinY A1
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

int desiredTemperature = 25, fahrenheitTemperature;
//int valueMQ4;
int valueMQ135;

//temperature variable
dht DHT;

int buttonState, buttonLastState; //joystick button states

int readHumiditySoil, humidityPercentSoil;

int motionDetectorValue = 0; //motion detector value

float alcoholValue;

//arrows
byte upArrow[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte downArrow[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};

byte leftArrow[] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B11111,
  B00010,
  B00100,
  B00000
};

byte rightArrow[] = {
  B00000,
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000
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
//  byte goUp;
//  byte goDown;
//  byte goLeft;
//  byte goRight;
};


//all menus initializations
MENU air_quality;
MENU alcohol_lvl;
MENU current_temp;
MENU new_temp;
MENU air_humidity;
MENU soil_state;
MENU *currentMenu = &air_quality;

void lcdRefresh()
{
  lcd.setCursor(2, 0);
  lcd.print(currentMenu->title);

  lcd.setCursor(0, 1);
  lcd.print(currentMenu->prefix);
  lcd.print(currentMenu->sensorValue);
  lcd.print(currentMenu->suffix);

  if (currentMenu->title == "Air quality:    ") {
    lcd.setCursor(0, 0);
    lcd.createChar(0, rightArrow);
    lcd.write(0);
    lcd.home();

    lcd.setCursor(1, 0);
    lcd.createChar(1, downArrow);
    lcd.write(1);
    lcd.home();

  }

  else if (currentMenu->title == "Temperature    ") {
    lcd.setCursor(0, 0);
    lcd.createChar(2, upArrow);
    lcd.write(2);
    lcd.home();

    lcd.setCursor(1, 0);
    lcd.createChar(3, downArrow);
    lcd.write(3);
    lcd.home();

  }

  else if (currentMenu->title == "Alcohol level:  ") {
    lcd.setCursor(0, 0);
    lcd.createChar(0, leftArrow);
    lcd.write(0);
    lcd.home();

  }

  else if (currentMenu->title == "Humidity:       ") {
    lcd.setCursor(0, 0);
    lcd.createChar(0, downArrow);
    lcd.write(0);
    lcd.home();

  }

  else if (currentMenu->title == "Soil state      ") {
    lcd.setCursor(0, 0);
    lcd.createChar(0, upArrow);
    lcd.write(0);
    lcd.home();

    lcd.setCursor(1, 0);
    lcd.createChar(1, downArrow);
    lcd.write(1);
    lcd.home();

  }

  else if (currentMenu->title == "Set new temp.:  ") {
    lcd.setCursor(0, 0);
    lcd.createChar(0, rightArrow);
    lcd.write(0);
    lcd.home();
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
//  air_quality.goUp = NULL;
//  air_quality.goDown = downArrow;
//  air_quality.goRight = rightArrow;
//  air_quality.goLeft = NULL;

  //menu for alcohol_lvl (subMenu of air_quality parent)
  alcohol_lvl.title = "Alcohol level:  ";
  alcohol_lvl.prevMenu = NULL;
  alcohol_lvl.nextMenu = NULL;
  alcohol_lvl.subMenu = NULL;
  alcohol_lvl.parent = &air_quality;
  alcohol_lvl.prefix = NULL;
  alcohol_lvl.suffix = "mg/l            ";
//  alcohol_lvl.goLeft = leftArrow;
//  alcohol_lvl.goRight = NULL;
//  alcohol_lvl.goDown = NULL;
//  alcohol_lvl.goUp = NULL;

  //menu for current_temp
  current_temp.title = "Temperature    ";
  current_temp.prevMenu = &air_quality;
  current_temp.subMenu = &new_temp;
  current_temp.parent = NULL;
  current_temp.nextMenu = &air_humidity;
  current_temp.prefix = "Current: ";
  current_temp.suffix = "C";

  //menu for new_temp (subMenu for current_temp
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
  lcd.setBacklight(HIGH);

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
  alcohol_lvl.sensorValue = alcoholValue;
  current_temp.sensorValue = DHT.temperature;
  air_humidity.sensorValue = DHT.humidity;
  soil_state.sensorValue = humidityPercentSoil;

  //soil state
  readHumiditySoil = analogRead(soilHumidity); //read sensor value
  humidityPercentSoil = map(readHumiditySoil, 1023, 0, 0, 100); //transform data in percent
  if (soil_state.sensorValue < 10) {
    soil_state.prefix = "Wet the soil!";
  } else if (humidityPercentSoil >= 10) {
    soil_state.prefix = "Poor value: ";
  } else if (humidityPercentSoil >= 50) {
    soil_state.prefix = "Good value: ";
  } else if (humidityPercentSoil == 100) {
    soil_state.prefix = "Too high... ";
  }

  //alcohol value
  if (alcohol_lvl.sensorValue > 450) {
    alcohol_lvl.prefix = "Alert! ";
  } else {
    alcohol_lvl.prefix = "Normal: ";
  }

  //motion detector
  motionDetectorValue = digitalRead(infraRedPin);
  if (motionDetectorValue == HIGH) {
    lcd.setBacklight(HIGH);
  } else {
    lcd.setBacklight(LOW);
  }

  //joystick UP | DOWN | RIGHT | LEFT
  if (analogRead(joyPinX) >= 600) { //UP
    joystick = joystick | JOYSTICK_UP ;
  }
  else if (analogRead(joyPinX) <= 512) { //DOWN
    joystick = joystick | JOYSTICK_DOWN ;
  }
  else if (analogRead(joyPinY) >= 600) { //RIGHT
    joystick = joystick | JOYSTICK_RIGHT;
    //lcd.setCursor(7, 1);
    //lcd.blink();

  }
  else if (analogRead(joyPinY) <= 400) { //LEFT
    joystick = joystick | JOYSTICK_LEFT;
  }

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

  if (joystick != oldJoystick)
  {
    //Serial.print("Joystick: ");
    //Serial.println(joystick);
    oldJoystick = joystick;
  }
  lcdRefresh();
}
