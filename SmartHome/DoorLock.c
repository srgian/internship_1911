#include <DoorLock.h>
#include <servo.h>
#include "Inputs.h"
#include "Outputs.h"

Servo myservo;  // creaza un obiect numit myservo

uint8_t lock;

void Doorlock() {
  myservo.attach(9);  // atasam pinul 9 la outputul de la servo
  Serial.begin(9600);
}

void DoorLockMainFunction(){
	 if( Serial.available()>0){
		 lock=Serial.read();
	 }

	 if(lock=='0'){
		 myservo.write(5);  // deschide poarta
		 delay(1500);
	 }

	 if(lock=='1'){
		 myservo.write(55);  // inchide poarta
		 delay(1500);  // Time to stay on line for servo to arrive its position.(Not Much Necessary)
	 }
}
