
#include <LiquidCrystal_I2C.h>

#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27,20,4);
const byte ROWS = 4; 
const byte COLS = 4; 
char keypressed;
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
 lcd.init();
 
 lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Enter code:");
  
     keypressed = customKeypad.getKey();
     if (keypressed =='A'){        //If A is pressed, activate the alarm
       
    }
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  static int i = 1;
  if (customKey){
    
    lcd.setCursor(i,1);
    lcd.print(customKey);
    Serial.println(customKey);
    delay(1000);
    lcd.setCursor(i,1);
    lcd.print("*");
    i++;
  }
}
