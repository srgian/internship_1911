#include "Outputs.h"
#include "Inputs.h"
#include "Comfort.h"
#include "Wire.h"
#include <dht.h>
extern dht DHT;
uint8_t joyButton;
extern float alcoholValue;
uint8_t  tempsts;
uint8_t dhtPin=A2;
int soilHumidity;


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


void ComfortInit()
{
  // lcdComfort.createChar(0, topUpDown);
    Print("DHT11 Humidity & temperature sensor:\n\n");
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
  new_temp.prefix = "*";
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
  lcdComfort.init();
  //lcd.setBacklight(HIGH);

    lcdComfort.createChar(0, topUpDown);
    lcdComfort.createChar(1, bottomUpDown);
    lcdComfort.createChar(2, middleUpDown);
    lcdComfort.createChar(3, rightArrow);
    lcdComfort.createChar(4, leftArrow);
    lcdComfort.createChar(5, almostHalf);
    lcdComfort.createChar(6, rightBlank);
    lcdComfort.createChar(7, almostFull);

    lcdComfort.clear();

  //joystick
  pinMode(joyButton, INPUT);
  digitalWrite(joyButton, HIGH);

  buttonLastState = digitalRead(joyButton);

  Serial.begin(9600);
 // lcdComfort.clear();

}




void ComfortMainFunction()
{
 /*byte opt[]= { 0b11111111};
lcdComfort.createChar(8, 0b11111111);
    lcdComfort.setCursor(0,0);
    lcdComfort.print((char)8);

lcdComfort.setBacklight(HIGH);

    return;
*/
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
  tempsts =(uint8_t)DHT.temperature;
  new_temp.sensorValue = newTemp;
  air_humidity.sensorValue = DHT.humidity;
  soil_state.sensorValue = humidityPercentSoil;

  //set new temp.
  if (newTemp == 37) {
    new_temp.suffix = "C-maxim point!";
    newTemp = 37;
  }
  else if (newTemp == 9) {
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
    lcdComfort.setBacklight(HIGH);
  }
  else {
    lcdComfort.setBacklight(LOW);
  }

  int pinX = analogRead(joyPinX);
  int pinY = analogRead(joyPinY);

  Serial.print("X: ");
  Serial.println(pinX);
  Serial.print("Y: ");
  Serial.println(pinY);

  //joystick UP | DOWN | RIGHT | LEFT
  if (pinY >= 500) { //UP, was 450
    joystick = joystick | JOYSTICK_UP ;
  }
  else if (pinY <= 330) { //DOWN, ok
    joystick = joystick | JOYSTICK_DOWN ;
  }
  else if (pinX >= 500) { //RIGHT, was 450
    joystick = joystick | JOYSTICK_RIGHT;
  }
  else if (pinX <= 330) { //LEFT, ok
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


