#include <Arduino.h>

int outputPin;
unsigned long pulse, deltaT;
const int diamWheel = 22;
const float kmIn = (100UL*1000)/2.54, hrMs = 1000UL*60*60, inMs = kmIn/hrMs, perimeter = diamWheel*PI;

void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
  Serial.print("In/ms: " + String(inMs) + "\nKilometers to inches: " + String(kmIn) + "\nHours to milliseconds: " + String(hrMs));
}

void loop() {
  if (outputPin == LOW && outputPin != digitalRead(2)) {
    deltaT = millis() - pulse;
    pulse = millis();

    if (deltaT == 0) {
      return;
    } else {
      Serial.println((1.0/deltaT)*inMs*perimeter, 10);
    }
  }
  
  outputPin = digitalRead(2);
}