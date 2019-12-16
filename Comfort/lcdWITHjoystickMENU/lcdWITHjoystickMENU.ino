#define joyButton 2
#define joyPinX A0
#define joyPinY A1
#define soilHumidity A7
#define infraPin 3

//Define Joystick keys
#define JOYSTICK_UP       B00000001
#define JOYSTICK_DOWN     B00000010
#define JOYSTICK_LEFT     B00000100
#define JOYSTICK_RIGHT    B00001000

#include "dht.h"

//temperature
#define dhtPin A2

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); //lcd object

int desiredTemperature = 25, fahrenheitTemperature;
int valueMQ4, valueMQ135;

dht DHT;

int buttonState, buttonLastState;

int readHumiditySoil, humidityPercentSoil;

int infraVal = 0;
bool motionState = false; // we start with no motion detected

void setup() {
  lcd.init();
  lcd.setBacklight(HIGH);

  pinMode(joyButton, INPUT);
  digitalWrite(joyButton, HIGH);

  buttonLastState = digitalRead(joyButton);
  Serial.begin(9600);
}

void loop() {
  //joystick
  unsigned char joystick = 0;
  static unsigned char oldJoystick = 0;

  //move right
  int moveRight = 0;
  int oldMoveRight = 0;
  int nv = 1;

  //read sensor values
  valueMQ4 = analogRead(A4);
  valueMQ135 = analogRead(A3);
  readHumiditySoil = analogRead(soilHumidity); //read sensor value
  humidityPercentSoil = map(readHumiditySoil, 1023, 0, 0, 100); //transform data in percent

  infraVal = digitalRead(infraPin);
  if (infraVal == HIGH) {
    lcd.setBacklight(HIGH);
  } else {
    lcd.setBacklight(LOW);
  }

  if (analogRead(joyPinX) >= 600) { //UP
    joystick = joystick | JOYSTICK_UP ;
  }
  else if (analogRead(joyPinX) <= 512) { //DOWN
    joystick = joystick | JOYSTICK_DOWN ;
  }
  else if (analogRead(joyPinY) >= 600 && nv == 1) { //RIGHT
    joystick = joystick | JOYSTICK_RIGHT;
    //lcd.setCursor(7, 1);
    //lcd.blink();
    if (moveRight == 0 && nv == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      DHT.read11(dhtPin);

      lcd.print("Humidity: ");
      lcd.print(DHT.humidity);
      lcd.print("%");

      lcd.setCursor(0, 1);
      lcd.print("Temp.: ");

      lcd.print(DHT.temperature);
      lcd.print("C");

      moveRight = 1;
      nv = 0;
    }

    if (moveRight == 1 && nv == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);

      lcd.print("Numero 2");

      moveRight = 2;
      nv = 0;
    }
  }
  else if (analogRead(joyPinY) <= 400) { //LEFT
    joystick = joystick | JOYSTICK_LEFT;
  }

  if ((joystick == JOYSTICK_UP) && (oldJoystick == 0))
  {
    Serial.println("Joystick up");
    lcd.clear();
    lcd.setCursor(0, 0);
    //valueMQ4 = analogRead(A4);
    lcd.print("Gas methane: ");
    lcd.setCursor(0, 1);
    lcd.print(valueMQ4);
    lcd.print("ppm");
  }
  else if ((joystick == JOYSTICK_DOWN) && (oldJoystick == 0))
  {
    Serial.println("Joystick down");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alcohol level: ");
    lcd.setCursor(0, 1);
    //valueMQ135 = analogRead(A3);

    //value of CO2 in ppm (parts per million)
    lcd.print(valueMQ135);
    if (valueMQ135 > 450)
    {
      lcd.print(" - Alert!");
    }
    else {
      lcd.print(" - Normal");
    }

  }
  else if ((joystick == JOYSTICK_LEFT) && (oldJoystick == 0))
  {
    Serial.println("Joystick left");

    lcd.clear();
    //readHumiditySoil = analogRead(soilHumidity); //read sensor value

    //humidityPercentSoil = map(readHumiditySoil, 1023, 0, 0, 100); //transform data in percent

    lcd.setCursor(0, 0);
    lcd.print("Soil state: ");
    lcd.print(humidityPercentSoil);
    lcd.print("%");

    if (humidityPercentSoil < 10) {
      lcd.setCursor(0, 1);
      lcd.print("Wet the soil!");
    } else if (humidityPercentSoil == 50) {
      lcd.setCursor(0, 1);
      lcd.print("Poor humidity");
    } else if (humidityPercentSoil >= 50) {
      lcd.setCursor(0, 1);
      lcd.print("Good humidity");
    } else if (humidityPercentSoil == 100) {
      lcd.setCursor(0, 1);
      lcd.print("Too high...");
    }
  }
  else if ((joystick == JOYSTICK_RIGHT) && (oldJoystick == 0))
  {
    Serial.println("Joystick right");

//    if (moveRight == 0 && nv == 1) {
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      DHT.read11(dhtPin);
//
//      lcd.print("Humidity: ");
//      lcd.print(DHT.humidity);
//      lcd.print("%");
//
//      lcd.setCursor(0, 1);
//      lcd.print("Temp.: ");
//
//      lcd.print(DHT.temperature);
//      lcd.print("C");
//
//      moveRight = 1;
//      nv = 0;
//    }
//
//    if (moveRight == 1 && nv == 1) {
//      lcd.clear();
//      lcd.setCursor(0, 0);
//
//      lcd.print("Numero 2");
//
//      moveRight = 2;
//      nv = 0;
//    }

  }

  if (joystick != oldJoystick)
  {
    //Serial.print("Joystick: ");
    //Serial.println(joystick);
    oldJoystick = joystick;
  }

  //  if (moveRight != oldMoveRight) {
  //    oldMoveRight = moveRight;
  //    Serial.print("move right: ");
  //    Serial.println(moveRight);
  //  }

  //delay(10);
}
