#define outputCLK 6
#define outputDT 7
#define pushButton 5

int counter = 24;
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
  aState = digitalRead(outputCLK); //current state of the CLK
  if (aState != aLastState) //if not, means it has changed its position
  { 
    if (digitalRead(outputDT) != aState) { //if DATA is not equal to the state, then ++ or --
      //counter++;
      if (counter >= 35) {
        Serial.println("Maxim point 35!");
        counter = 35;
      } else {
        counter++;
      }
    }
    else {
      if (counter <= 9) {
        Serial.println("Minim point 9!");
        counter = 9;
      } else {
        counter--;
      }
    }
    Serial.print("Temperature: ");
    Serial.println(counter);
  }
  aLastState = aState;

  //button pin...
  buttonState = digitalRead(pushButton);
  if ((buttonState == LOW) && (buttonLastState == HIGH))
  {
    Serial.println("Button pressed");
  }
  else if ((buttonState == HIGH) && (buttonLastState == LOW))
  {
    Serial.println("Button released");
  }
  else if ((buttonState == LOW) && ((buttonLastState == HIGH) || (buttonLastState == LOW)))
  {
    Serial.print("Holding temperature value: ");
    Serial.println(counter);
    delay(500);

  }

  buttonLastState = buttonState;

  delay(10);
}
