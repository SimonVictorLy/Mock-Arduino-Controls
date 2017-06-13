#include "StopWatch.h"

const int tachoPin = A0;    // select the input pin for the potentiometer

int tachoValue = 0;  // variable to store the value coming from the sensor
void setup() {
    Serial.begin(19200);
}

void loop() {
    tachoValue = analogRead(tachoPin);
    Serial.println(tachoValue);
}

