#include <IRremote.h>

const int analogOutPinUp = 13; // Analog output pin that the LED is attached to
const int analogOutPinDwn = 12;
const int analogOutPinLft = 11;
const int analogOutPinRht = 10;

const int trigPin = 6;
const int echoPin = 5;
const int buzzerOut = 4;
const int RECV_PIN = 7;

long duration = 0, distance = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerOut, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // Code will short here when a button is held down
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch(results.value){
      case (0xFF629D):
        Serial.println("up");
        analogWrite(analogOutPinUp, 255);
        break;
      case (0xFFA857):
        Serial.println("down");
        analogWrite(analogOutPinDwn, 255);
        break;
      case (0xFF22DD):
        Serial.println("left");
        analogWrite(analogOutPinLft, 255);
        break;
      case (0xFFC23D):
        Serial.println("right");
        analogWrite(analogOutPinRht, 255);
        break;
      case(0xFF02FD):
        Serial.println("all");
        analogWrite(analogOutPinUp, 255);
        delay(200);
        analogWrite(analogOutPinDwn, 255);
        delay(200);
        analogWrite(analogOutPinLft, 255);
        delay(200);
        analogWrite(analogOutPinRht, 255);
        delay(200);
        break;
       default:
        if (results.value< 0xFFFFFFFF){
           analogWrite(analogOutPinUp, 255);
            analogWrite(analogOutPinDwn, 255);
            analogWrite(analogOutPinLft, 255);
            analogWrite(analogOutPinRht, 255);
        }
    }
    irrecv.resume(); // Receive the next value
  }
  else{
      digitalWrite(trigPin, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/2) / 29.1;
      
      analogWrite(analogOutPinUp, 0);
      analogWrite(analogOutPinDwn, 0);
      analogWrite(analogOutPinLft, 0);
      analogWrite(analogOutPinRht, 0);
    }
  
  
  if (distance < 20) {  // This is where the LED On/Off happens
    
    analogWrite(analogOutPinUp, 255);
    analogWrite(analogOutPinDwn, 255);
    analogWrite(analogOutPinLft, 255);
    analogWrite(analogOutPinRht, 255);

    digitalWrite(buzzerOut,HIGH);
    delay(10);
    digitalWrite(buzzerOut,LOW);
    
  }
  else {
    digitalWrite(buzzerOut,LOW);
  }
  
  Serial.print(distance);
  Serial.println(" cm");
  delay(200);
}

