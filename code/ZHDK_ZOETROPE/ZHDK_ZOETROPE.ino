/*
 * Arduino ATTINY85 code for the IAD ZHdK Zoetrope 
 * Author: Luke Franzke 
 * luke.franzke@zhdk.ch 
 * 2017
 * This example code is in the public domain.
 */

const int analogInPin = A2;  // Distance sensor
const int analogInPin2 = A3;  // Poti for motor
const int digOutPin = 1; // LED
const int pwmOutPin = 0; //Motor
const int ledTrigger = 280;
const int maxLedTime = 25; // maximum duration of led flash

int sensorValue = 0;   // value read from the distance sensor
int motorSpeed=0;
int lightCount = 0;
boolean trigerTag = false;

int flashTime = 1; //duration of flash

void setup() {
  pinMode(digOutPin, OUTPUT);
  pinMode(pwmOutPin, OUTPUT);
  pinMode(analogInPin, INPUT);
  pinMode(analogInPin2, INPUT);
}

void loop() {
  lightCount++;
  sensorValue = analogRead(analogInPin);

  if (sensorValue >= ledTrigger && trigerTag == true) {
    lightCount = 0;
    trigerTag = false;
  }
  // make sure the led can't be trigered again imediatly 
  if (sensorValue < ledTrigger && lightCount >= flashTime*2) {
    trigerTag = true;
  }
  if (lightCount >= flashTime) {
    digitalWrite(digOutPin, LOW);
  } else { 

    digitalWrite(digOutPin, HIGH);

  }
  motorSpeed = map(analogRead(analogInPin2), 0, 1024, 0, 255);
   // Flash duration is maped to corelate to motor speed.
  flashTime = floor(map(motorSpeed, 0, 255, maxLedTime, 1)); 
  
  if (motorSpeed>=30) {
  analogWrite(pwmOutPin, motorSpeed);
  }
  // reset lightcount
  if (lightCount >= 1000) {
    lightCount = flashTime * 2;
  }
}
