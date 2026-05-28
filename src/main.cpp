#include <Arduino.h>

int currentOutput = LOW;
int lastOutput = LOW;

unsigned long pulse = 0;
unsigned long deltaT = 0;

const float kmIn = (100.0*1000.0)/2.54;
const float hrMs = 1000.0*60.0*60.0;
const float inMs = kmIn/hrMs;

const int diamWheel = 22;
const int magnet = 4;
const float perimeter = diamWheel*PI;

void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
  Serial.println("\nIn/ms: " + String(inMs) + "\nKilometers to inches: " + String(kmIn) + "\nHours to milliseconds: " + String(hrMs));
}

void loop() {
  currentOutput = digitalRead(2);

  if (lastOutput == HIGH && currentOutput == LOW) {
    deltaT = millis() - pulse;

    if (deltaT > 10) {
      pulse = millis();
      float revolutionT = deltaT * magnet;
      float speed = (perimeter / revolutionT) * (hrMs / kmIn);
      Serial.println(String(speed, 2) + "km/h");
    }
  }

  lastOutput = currentOutput;
}