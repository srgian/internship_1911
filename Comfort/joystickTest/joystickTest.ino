// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
//  Serial.print("Switch:  ");
//  Serial.print(digitalRead(SW_pin));
//  Serial.print("\n");
//  Serial.print("X-axis: ");
//  Serial.print(analogRead(X_pin));
//  Serial.print("\n");
//  Serial.print("Y-axis: ");
//  Serial.println(analogRead(Y_pin));
//  Serial.print("\n\n"); 

  if( analogRead(X_pin) >= 540){
    Serial.println("UP");
  }
  else if (analogRead(X_pin) <= 512){
    Serial.println("DOWN");
  }
  else if (analogRead(Y_pin) >= 540){
    Serial.println("RIGHT");
  }
  else if (analogRead(Y_pin) <= 400){
    Serial.println("LEFT");
  }

  delay(500);
}
