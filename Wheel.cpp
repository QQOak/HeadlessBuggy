#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(int ForwardsPin, int ReversePin, int SpeedPin) {
  this->ForwardsPin = ForwardsPin;
  this->ReversePin = ReversePin;
  this->SpeedPin = SpeedPin;
}
