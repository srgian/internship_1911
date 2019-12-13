#include "dht.h"

//temperature
#define dhtPin A2

//joystick
#define joyPinX A0
#define joyPinY A1

//rotary encoder
#define outputCLK 3
#define outputDT 4
#define pushButton 5


//Define Joystick keys
#define JOYSTICK_UP       B00000001
#define JOYSTICK_DOWN     B00000010
#define JOYSTICK_LEFT     B00000100
#define JOYSTICK_RIGHT    B00001000

int desiredTemperature = 25, fahrenheitTemperature;
int valueMQ4, valueMQ135;

dht DHT;

int aState;
int aLastState;
int buttonState;
int buttonLastState;

void setup() {
  pinMode(outputCLK, INPUT);
  pinMode(outputDT, INPUT);
  pinMode(pushButton, INPUT);

  Serial.begin(9600);

  aLastState = digitalRead(outputCLK); //current position
  buttonLastState = digitalRead(pushButton);
}

void loop() {
  static int x= 0;
  //joystick
  unsigned char joystick = 0;
  static unsigned char oldJoystick = 0;
  //Handle Joystick

  //Handle DHT

  //


  //handle data
  
  int joyX = analogRead(joyPinX);
  int joyY = analogRead(joyPinY);
  if (joyX >= 600) { //UP
    joystick = joystick | JOYSTICK_UP ;
    //detect gas metane - MQ4
    Serial.println("|||Joystick UP|||");
    valueMQ4 = analogRead(A4);
    Serial.print("Gas methane: ");
    Serial.print(valueMQ4);
    Serial.println("ppm <parts-per-million>\n\n\n");
  }
  else if (joyX <= 512) { //DOWN
    joystick = joystick | JOYSTICK_DOWN;
    
    //detect alcohol - MQ135
    Serial.println("|||Joystick DOWN|||");
    valueMQ135 = analogRead(A3);
    Serial.print("Alcohol level: ");
    Serial.print(valueMQ135);
    if (valueMQ135 > 350)
    {
      Serial.println(" - Alert!");
    }
    else {
      Serial.println(" - Normal");
    }

    //detect CO2 - MQ135
    Serial.print("CO2: ");
    Serial.print(valueMQ135);
    Serial.println("ppm <parts-per-million>\n\n\n");
  }
  else if (joyY >= 600 ) { //RIGHT
    joystick = joystick | JOYSTICK_RIGHT;
    //temperature & humidity
    //Serial.println("|||Joystick RIGHT|||");

    if(x == 0) 
    {
      DHT.read11(dhtPin);
      Serial.println("\n\n\n\n\nDHT.read11");
    }
    x = (x + 10) % 1000;

    //Serial.print("Humidity: ");
    //Serial.print(DHT.humidity);
    //Serial.print("%\n");
    Serial.print("Current temperature: ");
    Serial.println(desiredTemperature);

    aState = digitalRead(outputCLK); //current state of the CLK
    if (aState != aLastState) //if not, means it has changed its position
    {
      if (digitalRead(outputDT) != aState) { //if DATA is not equal to the state, then ++ or --
        //counter++;
        if (desiredTemperature >= 35) {
          Serial.println("Maxim point 35!");
          desiredTemperature = 35;
        } else {
          desiredTemperature++;
        }
      }
      else {
        if (desiredTemperature <= 9) {
          Serial.println("Minim point 9!");
          desiredTemperature = 9;
        } else {
          desiredTemperature--;
        }
      }
      Serial.print("New temperature: ");
      Serial.println(desiredTemperature);
    }
    aLastState = aState;
    Serial.println("\n\n");

  }
  else if (joyY <= 400) {
    joystick = joystick | JOYSTICK_LEFT;
    //Serial.println("|||Joystick LEFT|||");
    //Serial.println("Altitude | Pressure\n\n");
  }
  
  if((joystick == JOYSTICK_LEFT) && (oldJoystick  == 0))
  {
      Serial.println("Joystick stanga");
  }
  
  if(joystick != oldJoystick)
  {
    Serial.print("Joystick: ");
    Serial.println(joystick);
    oldJoystick = joystick;
  }
  
  delay(10);
}
