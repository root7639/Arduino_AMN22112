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

int interval = 50;

int HIGH_LED = 13; //red
int LOW_LED = 3; //blue

int motionSensor = 0;
int motionSensorBefore = 0;
int sensorTilt = 0;
int sensorTiltBefore = 0;

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

int person = 0;
int sensorTiltNum = 0;

int motionTilt[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*
 * motion[]
 * plus = 2
 * minus = 1
 * zero = 0
 */

void updateMotionSensor () {
  motionSensorBefore = motionSensor;
  sensorTiltBefore = sensorTilt;
  motionSensor = analogRead(A0);
  motionSensor = fir.filter(motionSensor);
  sensorTilt = (motionSensor - motionSensorBefore) / 5;
  delay(interval);
}

void setup() {
  Serial.begin(9600);

  pinMode(HIGH_LED, OUTPUT);
  pinMode(LOW_LED, OUTPUT);

}

void loop() {
  
  updateMotionSensor();
  
  //Serial.println(motionSensor);

  //make vertical line per one sec
  //Serial.print(millis()/1000%2*1600);
  //Serial.print(",");

  /*
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
  */

  //motion sensor's gragh tilt
  //int sensorTilt = (motionSensor - motionSensorBefore) / 5;

  //Serial.println(sensorTilt);

  /*
  if (motionSensor > 600 || motionSensor < 300){
    //process when detected motion peak
    return;
  }
  */

  if (sensorTilt != 0) {

    for (int i = 0; i < 10; i++) {
      
      if (sensorTilt > 0) {
        motionTilt[i] = 2;
        
      } else if (sensorTilt < 0) {
        motionTilt[i] = 1;
        
      } else {
        
        for (int j = 0; j < 10; j++) {
          updateMotionSensor();
          if (sensorTilt == 0){
            sensorTiltNum++;
          }
        }
        if (sensorTiltNum > 7){
          break;
        }
        
      }

      updateMotionSensor();

      int loopNum = 0;
      while ((sensorTiltBefore >= 0) == (sensorTilt >= 0)){
        updateMotionSensor();
        loopNum++;
        if (loopNum > 10) {
          break;
        }
      }
    }

    for (int i = 0; i < 10; i++) {
      Serial.print(motionTilt[i]);
      motionTilt[i] = 0;
    }
    Serial.println(";");
  }
  sensorTiltNum = 0;
  
}



//time person passing is about 4000ms
