#include "StopWatch.h"

const int sensorPin = A0;    // select the input pin for the potentiometer

int sensorValue = 0;  // variable to store the value coming from the sensor
float RPM = 0;
int count = 0;

enum fsm {INITIALIZE,OFFSTATE, ONSTATE};
enum fsm state  = INITIALIZE;

StopWatch timer;  // Default is MILLIS

void setup() {
    Serial.begin(9600);
}

void loop() {

  switch (state){
    case (INITIALIZE):
      timer.start();
      sensorValue = analogRead(sensorPin);
      count = 0;
      state = (sensorValue > 20) ? ONSTATE : OFFSTATE;
      break;
    
    case (OFFSTATE):
        sensorValue = analogRead(sensorPin);
        
        //Serial.println(0);

        if (sensorValue>150) {
          timer.stop();
          timer.reset();
          timer.start();
          
          state = ONSTATE;
          count = 0;
        }
      break;
   
    case (ONSTATE):
      sensorValue = analogRead(sensorPin);
      count = sensorValue < 150 ? count + 1 : 0;

      //Serial.println(1);

      if (count>4) {
        state = OFFSTATE;
        count = 0;
      }
    
      break;
  }
}

void calculateRPM(){
}
