#define joyButton 2
#define joyPinX A0
#define joyPinY A1
#define soilHumidity A7
#include "dht.h"

//temperature
#define dhtPin A2

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int desiredTemperature = 25, fahrenheitTemperature;
int valueMQ4, valueMQ135;

dht DHT;

int buttonState;
int buttonLastState;

int readHumiditySoil;
int humidityPercentSoil;

void setup() {
  lcd.init();
  lcd.setBacklight(HIGH);

  pinMode(joyButton, INPUT);
  digitalWrite(joyButton, HIGH);

  buttonLastState = digitalRead(joyButton);
}

void loop() {

  if (analogRead(joyPinX) >= 600) { //UP
    lcd.clear();
    lcd.setCursor(0, 0);
    valueMQ4 = analogRead(A4);
    lcd.print("Gas methane: ");
    lcd.setCursor(0, 1);
    lcd.print(valueMQ4);
    lcd.print("ppm");
  }
  else if (analogRead(joyPinX) <= 512) { //DOWN
    lcd.clear();
    lcd.setCursor(0, 0);
    valueMQ135 = analogRead(A3);
    lcd.print("Alcohol level: ");
    lcd.setCursor(0, 1);

    lcd.print(valueMQ135);
    if (valueMQ135 > 450)
    {
      lcd.print(" - Alert!");
    }
    else {
      lcd.print(" - Normal");
    }
  }
  else if (analogRead(joyPinY) >= 600) {
    lcd.clear();
    lcd.setCursor(0, 0);
    DHT.read11(dhtPin);
    lcd.print("Humidity: ");
    lcd.print(DHT.humidity);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("Temp.: ");
    lcd.print(desiredTemperature);
    lcd.print("C");
  }
  else if (analogRead(joyPinY) <= 400) {
    lcd.clear();
    readHumiditySoil = analogRead(soilHumidity); //read sensor value

    humidityPercentSoil = map(readHumiditySoil, 1023, 0, 0, 100); //transform data in percent

    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    //    if (humidityPercentSoil == 100)
    //      lcd.print(" ");

    lcd.print(humidityPercentSoil);
    lcd.print("%");
    
    if (humidityPercentSoil < 10) {
      lcd.setCursor(0, 1);
      lcd.print("Uda gradina!!!");
    }

  }


}
