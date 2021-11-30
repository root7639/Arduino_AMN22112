//this program made for AMN22112 Panasonic

int HIGH_LED = 2;
int LOW_LED = 3;

void setup() {
  Serial.begin(9600);

  pinMode(HIGH_LED, OUTPUT);
  pinMode(LOW_LED, OUTPUT);
}

void loop() {
  
  int motionSensor;
  motionSensor = analogRead(A0);
  
  Serial.println(motionSensor);

  //make vertical line per one sec
  Serial.print(millis()/1000%2*1600);
  Serial.print(",");

  if (motionSensor > 600){
    digitalWrite(HIGH_LED, HIGH);
  } else {
    digitalWrite(HIGH_LED, LOW);
  }

  if (motionSensor < 300){
    digitalWrite(LOW_LED, HIGH);
  } else {
    digitalWrite(LOW_LED, LOW);
  }
  
  delay(50);
  
}
