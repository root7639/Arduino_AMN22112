//this program made for AMN22112 Panasonic

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  int motionSensor;
  motionSensor = analogRead(A0);
  
  Serial.println(motionSensor);

  //make vertical line per one sec
  Serial.print(millis()/1000%2*1600);
  Serial.print(",");
  
  delay(50);
}
