#include "dht.h"
#define dht_apin A4 // Analog Pin 4

dht DHT;

uint8_t valueMQ135, valueMQ4;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  valueMQ135 = analogRead(A0);

  Serial.println("***loading***");
  //detect alcohol - MQ135
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

  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.print("%\n");
  Serial.print("Temperature: ");
  Serial.print(DHT.temperature);
  Serial.print("°C; ");

  Serial.print(DHT.temperature * 1.8 + 32);
  Serial.println("°F\n");
  
  Serial.println("\n");
  delay(2000);
}
