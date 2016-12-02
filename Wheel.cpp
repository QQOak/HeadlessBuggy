#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(int ForwardsPin, int ReversePin, int SpeedPin) {
  this->ForwardsPin = ForwardsPin;
  this->ReversePin = ReversePin;
  this->SpeedPin = SpeedPin;

  ConfigureWheelPins();
}

void Wheel::ConfigureWheelPins() {
  
  pinMode(this->ForwardsPin, OUTPUT);
  pinMode(this->ReversePin, OUTPUT);
  pinMode(this->SpeedPin, OUTPUT);
  
  digitalWrite(this->ForwardsPin, false);
  digitalWrite(this->ReversePin, false);
  analogWrite(this->SpeedPin, 0);
  
}

