#include "dht.h"
#define dht_apin A4 // analog pin 4

int buttonUp = 2; //digital pin 2
int buttonUpState = 0;

int buttonDown = 4; //digital pin 4
int buttonDownState = 0;

int incrementState = 0; //increment 1000 times this value...
int delayMilliseconds = 10; //delay for 'void loop'

int previousStateButtonUp, previousStateButtonDown;

dht DHT;

int desiredTemperature, fahrenheitTemperature;

uint8_t valueMQ135, valueMQ4;

int regPotentiometer;

void setup()
{
  Serial.begin(115200);

  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(regPotentiometer, INPUT);

  desiredTemperature = 25;
}
void loop()
{
  if (incrementState % 5000  == 0)
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
  }
  
  //read analog regPotentiometer
  regPotentiometer = analogRead(A6);

  //after each 2 seconds...
  if (incrementState % 2000  == 0) 
  {
    Serial.println("***temperature loading***");
    DHT.read11(dht_apin);
    normalTemperature();
  }
  
  if (incrementState % 50  == 0) 
  {
    buttonUpState = digitalRead(buttonUp);
    buttonDownState = digitalRead(buttonDown);
    
    if (buttonDownState == HIGH && previousStateButtonDown == 0)
    {
      Serial.println("PushDown button activated");
      DownTemperature();
    }
    else if (buttonUpState == HIGH && previousStateButtonUp == 0)
    {
      Serial.println("PushUp button activated");
      UpTemperature();

    }
     
    previousStateButtonUp = buttonUpState;
    previousStateButtonDown = buttonDownState;
  }

  delay(delayMilliseconds);
  incrementState = incrementState + 10;
  if (incrementState == 10000) {
    incrementState = 0;
  }
}

int normalTemperature() {
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.print("%\n");
  Serial.print("Temperature: ");
  regPotentiometer = map(regPotentiometer, 0, 1023, 0, 40);

  if (desiredTemperature >= 35 && fahrenheitTemperature >= 95) {
    Serial.println("Maxim point! 35°C | 95°F");
    
  }
  else if (desiredTemperature <= 9 && fahrenheitTemperature <= 48.2) {
    Serial.println("Minim point! 9°C | 48.2°F");
    
  } else {
    //Serial.print(DHT.temperature);
    Serial.print(desiredTemperature);
    Serial.print("°C; ");
    //Serial.print(DHT.temperature * 1.8 + 32);
    Serial.print(desiredTemperature * 1.8 + 32);
    Serial.println("°F\n");
  }
}

int UpTemperature() {

  desiredTemperature++;
  fahrenheitTemperature = (desiredTemperature * 1.8 + 32) + 1;

  //maxim point
  if (desiredTemperature >= 35 && fahrenheitTemperature >= 95) {
    Serial.println("Maxim point! 35°C | 95°F");
  }
  else {
    Serial.print("Set new Temperature: ");
    Serial.print(desiredTemperature);
    Serial.print("°C; ");
    Serial.print(fahrenheitTemperature);
    Serial.println("°F\n");
  }
}

int DownTemperature() {

  desiredTemperature--;
  fahrenheitTemperature = (desiredTemperature * 1.8 + 32) - 1;

  //minim point
  if (desiredTemperature <= 9 && fahrenheitTemperature >= 48.2) {
    Serial.println("Minim point! 9°C | 48.2°F");
  }
  else {
    Serial.print("Set new Temperature: ");
    Serial.print(desiredTemperature);
    Serial.print("°C; ");
    Serial.print(fahrenheitTemperature);
    Serial.println("°F\n");
  }
}
