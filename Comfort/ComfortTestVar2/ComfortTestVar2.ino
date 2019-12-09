#include "dht.h"

#define dhtPin A2
#define joyPinX A0
#define joyPinY A1
const int SW_pin = 2; // digital pin connected to switch output

int desiredTemperature = 25, fahrenheitTemperature;
int valueMQ4, valueMQ135;

dht DHT;


void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

}

void loop() {
  Serial.println("***loading***");
  //joystick
  if (analogRead(joyPinX) >= 540) { //UP
    //detect gas metane - MQ4
    valueMQ4 = analogRead(A4);
    Serial.print("Gas methane: ");
    Serial.print(valueMQ4);
    Serial.println("ppm <parts-per-million>\n");
  }
  else if (analogRead(joyPinX) <= 512) { //DOWN
    //detect alcohol - MQ135
    valueMQ135 = analogRead(A3);
    Serial.print("Alcohol level: ");
    Serial.print(valueMQ135);
    if (valueMQ135 > 300)
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
  }
  else if (analogRead(joyPinY) >= 540 ) {
    //temperature & humidity    DHT.read11(dht_apin);
    Serial.print("Humidity: ");
    Serial.print(DHT.humidity);
    Serial.print("%\n");
    Serial.print("Temperature: ");
  }
  else if (analogRead(joyPinY) <= 400){
    Serial.println("Altitude | Pressure");
  }


  delay(500);



}
