#include <IRremote.h>

const int analogOutPinUp = 13; // Analog output pin that the LED is attached to
const int analogOutPinDwn = 12;
const int analogOutPinLft = 11;
const int analogOutPinRht = 10;

int RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {

    switch(results.value){
      case (16736925):
        Serial.println("up");
        analogWrite(analogOutPinUp, 255);
        break;
      case (16754775):
        Serial.println("down");
        analogWrite(analogOutPinDwn, 255);
        break;
      case (16720605):
        Serial.println("left");
        analogWrite(analogOutPinLft, 255);
        break;
      case (16761405):
        Serial.println("right");
        analogWrite(analogOutPinRht, 255);
        break;
      case(16712445):
        Serial.println("all");
        analogWrite(analogOutPinUp, 255);
        analogWrite(analogOutPinDwn, 255);
        analogWrite(analogOutPinLft, 255);
        analogWrite(analogOutPinRht, 255);
        break;
    }
    irrecv.resume(); // Receive the next value
    delay(100);
  }
  else{
        analogWrite(analogOutPinUp, 0);
        analogWrite(analogOutPinDwn, 0);
        analogWrite(analogOutPinLft, 0);
        analogWrite(analogOutPinRht, 0);
    }
  delay(100);
}

