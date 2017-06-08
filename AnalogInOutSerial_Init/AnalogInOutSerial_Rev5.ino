/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
// These constants won't change.  They're used to give names
// to the pins used:

const int analogInPinBtn = A0;
const int analogInPinX = A5;  // Analog input pin that the potentiometer is attached to
const int analogInPinY = A7;

const int analogOutPinUp = 13; // Analog output pin that the LED is attached to
const int analogOutPinDwn = 12;
const int analogOutPinLft = 11;
const int analogOutPinRht = 10;


int sensorValueX = 0;        // value read from the pot
int sensorValueY = 0;        // value read from the pot
int buttonValue = 0;

int outputValueUp = 0;        // value output to the PWM (analog out)
int outputValueDwn = 0;        // value output to the PWM (analog out)
int outputValueLft = 0;        // value output to the PWM (analog out)
int outputValueRht = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void sequence(){
    int i = 0;
    int j = 0;
    int pins[4] = {analogOutPinUp,analogOutPinRht,analogOutPinDwn,analogOutPinLft};
    
    for (i = 0; i<2;i++){
          for (j=0; j<4;j++){
              analogWrite(pins[j], 255);
              delay(200);
              analogWrite(pins[j], 0);
          }
    }
    
    for (i = 0; i<2; i++){
          for (j=0; j<4;j++){
              analogWrite(pins[j], 255);
          }
          delay(500);
          for (j=0; j<4;j++){
              analogWrite(pins[j], 0);
          }
          delay(200);
    }
}

void loop() {
  // read the analog in value:
  sensorValueX = analogRead(analogInPinX);
  sensorValueY = analogRead(analogInPinY);
  buttonValue = analogRead(analogInPinBtn);
  
  // map it to the range of the analog out:
  outputValueUp = map(constrain(sensorValueY,0,511), 511, 0, 0, 255);
  outputValueDwn = map(constrain(sensorValueY,512,1023), 512, 1023, 0, 255);
  outputValueLft = map(constrain(sensorValueX,0,511), 511, 0, 0, 255);
  outputValueRht = map(constrain(sensorValueX,512,1023),512, 1023, 0, 255);
  
  // change the analog out value:
  analogWrite(analogOutPinUp, outputValueUp);
  analogWrite(analogOutPinDwn, outputValueDwn);
  analogWrite(analogOutPinLft, outputValueLft);
  analogWrite(analogOutPinRht, outputValueRht);
  
  if (buttonValue < 20 && (sensorValueX > 480 && sensorValueX < 540) && (sensorValueY > 480 && sensorValueY < 540) ){
    sequence();
  }


  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValueX);
  Serial.print(", ");
  Serial.print(sensorValueY);
  
  Serial.print("\t output = Up ");
  Serial.print(outputValueUp);
  Serial.print(", Down ");
  Serial.print(outputValueDwn);
  Serial.print(", Left ");
  Serial.print(outputValueLft);
  Serial.print(", Right ");
  Serial.print(outputValueRht);

   Serial.print("\t Button = ");
  Serial.println(buttonValue);


  
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
