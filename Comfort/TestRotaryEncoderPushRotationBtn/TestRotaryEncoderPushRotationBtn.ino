#define outputA 6
#define outputB 7
#define pushButton 5

int counter = 0;
int aState;
int aLastState;
int buttonState = 0;
int buttonLastState;

void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(pushButton, INPUT);

  Serial.begin(9600);

  aLastState = digitalRead(outputA);
  buttonLastState = digitalRead(pushButton); 

}

void loop() {
  aState = digitalRead(outputA);
  if (aState != aLastState) {
    if (digitalRead(outputB) != aState) {
      counter++;
    } else {
      counter--;
    }
    Serial.print("Position: ");
    Serial.println(counter);
  }
  aLastState = aState;

  //button pin...
  buttonState = digitalRead(pushButton);
  if ((buttonState == HIGH) && (buttonLastState == LOW))
  {
    Serial.println("You pressed the button");
  }
  buttonLastState = buttonState;

  delay(10);
}
