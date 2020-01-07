#include "dht.h"
#define dht_apin A4 // analog pin 4

int buttonUp = 2; //digital pin 2
int buttonUpState = 0;

int buttonDown = 4; //digital pin 4
int buttonDownState = 0;

int incrementState = 0; //increment 1000 times this value...
int delayMilliseconds = 1000; //delay for 'void loop'

int previousStateButtonUp, previousStateButtonDown;

dht DHT;

int desiredTemperature, fahrenheitTemperature;

uint8_t valueMQ135, valueMQ4;

int regPotentiometer;

void setup()
{
  Serial.begin(9600);

  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(regPotentiometer, INPUT);

  desiredTemperature = 25;
}
void loop()
{
  Serial.println("***loading***");
  //detect alcohol - MQ135
  valueMQ135 = analogRead(A0);
  Serial.print("Alcohol level: ");
  Serial.print(valueMQ135);
  if (valueMQ135 > 220)
  {
    Serial.println(" - Alert!\n");
  }
  else {
    Serial.println(" - Normal\n");
  }

  //detect CO2 - MQ135
  Serial.print("CO2: ");
  Serial.print(valueMQ135);
  Serial.println("ppm <parts-per-million>\n");

  //detect gas metane - MQ4
  valueMQ4 = analogRead(A2);
  Serial.print("Gas methane: ");
  Serial.print(valueMQ4);
  Serial.println("ppm <parts-per-million>\n");

  //humidity & temperature
  DHT.read11(dht_apin);

  //read analog regPotentiometer
  regPotentiometer = analogRead(A6);
  regPotentiometer = map(regPotentiometer, 0, 1023, 0, 40);

  //read the state of the pushButton value
  buttonUpState = digitalRead(buttonUp);
  buttonDownState = digitalRead(buttonDown);

  //after each 2 seconds...
  if (incrementState % 2000  == 0) {
    Serial.println("***temperature loading***");
    if (buttonDownState == HIGH && previousStateButtonDown == 0)
    {
      Serial.println("PushDown button activated");

      DownTemperature();
      //buttonDownState = LOW;
    }
    else if (buttonUpState == HIGH && previousStateButtonUp == 0)
    {
      Serial.println("PushUp button activated");

      UpTemperature();
      //buttonUpState = LOW;

    }
    else {
      normalTemperature();
    }
  }

  
  previousStateButtonUp = buttonUpState;
  previousStateButtonDown = buttonDownState;

  Serial.println("\n");

  delay(delayMilliseconds);
    incrementState = incrementState + 1000;
    if (incrementState == 10000) {
      incrementState = 0;
    }
}

int normalTemperature() {
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.print("%\n");
  Serial.print("Temperature: ");
  fahrenheitTemperature = (regPotentiometer * 1.8 + 32) + 1;

  if (regPotentiometer >= 35 && fahrenheitTemperature >= 95) {
    Serial.println("Maxim point! 35°C | 95°F");

  }
  else if (regPotentiometer <= 9 && fahrenheitTemperature <= 48.2) {
    Serial.println("Minim point! 9°C | 48.2°F");

  } else {
    //Serial.print(DHT.temperature);
    Serial.print(regPotentiometer);
    Serial.print("°C; ");
    //Serial.print(DHT.temperature * 1.8 + 32);
    Serial.print(regPotentiometer * 1.8 + 32);
    Serial.println("°F\n");
  }
}

int UpTemperature() {

  regPotentiometer++;
  fahrenheitTemperature = (regPotentiometer * 1.8 + 32) + 1;

  //maxim point
  if (regPotentiometer >= 35 && fahrenheitTemperature >= 95) {
    Serial.println("Maxim point! 35°C | 95°F");
  }
  else {
    Serial.print("Set new Temperature: ");
    Serial.print(regPotentiometer);
    Serial.print("°C; ");
    Serial.print(fahrenheitTemperature);
    Serial.println("°F\n");
  }
}

int DownTemperature() {

  regPotentiometer--;
  fahrenheitTemperature = (regPotentiometer * 1.8 + 32) - 1;

  //minim point
  if (regPotentiometer <= 9 && fahrenheitTemperature >= 48.2) {
    Serial.println("Minim point! 9°C | 48.2°F");
  }
  else {
    Serial.print("Set new Temperature: ");
    Serial.print(regPotentiometer);
    Serial.print("°C; ");
    Serial.print(fahrenheitTemperature);
    Serial.println("°F\n");
  }
}