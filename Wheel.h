#ifndef Wheel_h
#define Wheel_h

#include "Arduino.h"


class Wheel {
public:
  Wheel(int ForwardsPin, int ReversePin, int SpeedPin);
  int ForwardsPin;
  int ReversePin;
  int SpeedPin;  
};

#endif
