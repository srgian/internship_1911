#include <DoorLock.h>
#include <servo.h>
#include "Inputs.h"
#include "Outputs.h"

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

uint8_t lock;

void Doorlock() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void DoorLockMainFunction(){
	 if( Serial.available()>0){
		 lock=Serial.read();
	 }
	 
	 if(lock==false){
		 myservo.write(5);  // Unlock position in my case modify according to yours
		 delay(1500);  // Time to stay on line for servo to arrive its position.(Not Much Necessary)
	 }
	 
	 if(lock==true){
		 myservo.write(55);  // lock position in my case modify according to yours
		 delay(1500);  // Time to stay on line for servo to arrive its position.(Not Much Necessary)
	 }
}