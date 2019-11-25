#define LED 10
#define Button1 12
#define Button2 13
int stateB1;
int stateB2;
int pvs_state1;
int pvs_state2; 
int led_state=LOW;

void setup() {                
  pinMode(Button1, INPUT); 
  pinMode(LED, OUTPUT); 
}


void loop() {
  stateB1 = digitalRead(Button1); 
  stateB2=digitalRead(Button2);
  if(
    (pvs_state1==1 && stateB1==0) ||
    (pvs_state2 && stateB2==0)
    )
  {
    if(led_state==LOW)
    {
      led_state=HIGH;
    } else {
      led_state=LOW;
    }
  }
  
  pvs_state1=stateB1;
  pvs_state2=stateB2;
  digitalWrite(LED,led_state);
  delay(100); }
  
