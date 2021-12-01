/*
 * this program made for AMN22112 Panasonic
 * 
 * need library from https://github.com/tttapa/Filters.git
 * git clone to Library/Arduino15/ (Mac)
 * 
 * Degital filter design services
 * http://dsp.jpn.org/dfdesign/fir/mado.shtml
 * 
 */

#include <FIRFilter.h>

int HIGH_LED = 2;
int LOW_LED = 3;

//degital filter by degital filter design services
const double a[] = {
    6.237074932031003e-19,  1.203468256554930e-03,  2.789059944207731e-03,  4.234500608097008e-03,
    3.949464324766553e-03,  -2.416866536162014e-18, -8.270810074278890e-03, -1.861479317048980e-02,
    -2.543297162983507e-02, -2.127139910497268e-02, 6.003184622079840e-18,  3.965539443147850e-02,
    9.204504649186659e-02,  1.453456837490316e-01,  1.852171297065770e-01,  2.000000000000000e-01,
    1.852171297065770e-01,  1.453456837490316e-01,  9.204504649186659e-02,  3.965539443147850e-02,
    6.003184622079840e-18,  -2.127139910497268e-02, -2.543297162983507e-02, -1.861479317048980e-02,
    -8.270810074278890e-03, -2.416866536162014e-18, 3.949464324766553e-03,  4.234500608097008e-03,
    2.789059944207731e-03,  1.203468256554930e-03,  6.237074932031003e-19};

//FIRFilter
FIRFilter fir(a); 

void setup() {
  Serial.begin(9600);

  pinMode(HIGH_LED, OUTPUT);
  pinMode(LOW_LED, OUTPUT);
}

void loop() {
  
  int motionSensor;
  motionSensor = analogRead(A0);
  motionSensor = fir.filter(motionSensor); //Apply FIRFilter
  
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
