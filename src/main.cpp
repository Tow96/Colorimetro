#include <Arduino.h>
#define onboard 13

void setup() {
  pinMode(onboard, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(onboard, HIGH);
  delay(1000);
  digitalWrite(onboard, LOW);
  delay(1000);
  Serial.println("full loop");
}