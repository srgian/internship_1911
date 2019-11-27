int sensorValue;

void setup(){
  Serial.begin(9600);
  Serial.println("MQ 135 Gas Sensor\n");
  
}

void loop(){

  ReadImputs();
  Logic();
  WriteOuputs();
  Serial.println("*****loading*****\n");

  sensorValue = analogRead(A0);

  Serial.print("CO2: ");
  Serial.print(sensorValue);
  Serial.println("ppm <parts-per-million>");
  Serial.println();
  delay(2000);
}
