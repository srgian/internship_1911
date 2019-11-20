#include "dht.h"
#define dht_apin A0 // Analog Pin 0

dht DHT;

void setup() {

  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature sensor:\n\n");
  delay(1000);//Wait before accessing Sensor

}

void loop() {
  DHT.read11(dht_apin);

  Serial.println("***Current data***");
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.print("%  \n");
  Serial.print("Temperature: ");
  Serial.print(DHT.temperature);
  Serial.println("C  \n");

  delay(3000);//Wait 3 seconds before accessing sensor again

}
