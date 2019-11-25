#include <Keypad.h>

const int Led_A = 10;
const int Led_B = 11;
const int Led_C = 12;

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(Led_A,OUTPUT); 
  pinMode(Led_B,OUTPUT);
  pinMode(Led_C,OUTPUT);
  
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
    switch(customKey)
    {
      case '1':
      //digitalWrite(Led_A,HIGH); //se aprinde becurile daca apasam pe 1 
      digitalWrite(Led_A, !digitalRead(Led_A));
      delay(500);
      break;
    
      case '2':
       digitalWrite(Led_B, !digitalRead(Led_B));
      break;
      
      case '3':
      digitalWrite(Led_C, !digitalRead(Led_C));
      break;
    
     
      case 'A':
      digitalWrite(Led_A,HIGH);
      digitalWrite(Led_B,HIGH);
      digitalWrite(Led_C,HIGH); //se aprind toate becurile daca apasam pe A
      break;
      
      case '5':
      digitalWrite(Led_B,HIGH);
      digitalWrite(Led_C,HIGH); //se aprinde becul 2 si 3
      break;
      
      case '6':
      digitalWrite(Led_A,HIGH);
      digitalWrite(Led_C,HIGH); //se aprinde becul 1 si 3
      break;
      
      case 'C':
      digitalWrite(Led_A,HIGH); //se aprind 1 cate 1 cu delay de 2s
      delay(1000);
      digitalWrite(Led_B,HIGH); 
      delay(1000);
      digitalWrite(Led_C,HIGH); 
      delay(1000);

      digitalWrite(Led_A,LOW); //se aprind 1 cate 1 cu delay de 2s
      delay(1000);
      digitalWrite(Led_B,LOW); 
      delay(1000);
      digitalWrite(Led_C,LOW); 
      delay(1000);
      break;
      
      case '*':
      digitalWrite(Led_A,HIGH); //se aprind 1 cate 1 cu delay de 1s
      delay(1000);
      digitalWrite(Led_B,HIGH); 
      delay(1000);
      digitalWrite(Led_C,HIGH); 
      delay(1000);
      break;
     
     
     case '0': // sa oprim becurile cu tasta 0
     digitalWrite(Led_A,LOW);
     digitalWrite(Led_B,LOW);
     digitalWrite(Led_C,LOW);
     break;
    
    }
  }
}
