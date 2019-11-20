extern int temt6000Pin;
extern HardwareSerial Serial;
void x()
{
    int value = analogRead(temt6000Pin);
  Serial.println(value); 
  delay(200);
}
