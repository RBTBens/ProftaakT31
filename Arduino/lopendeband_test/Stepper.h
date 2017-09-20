#ifndef __STEPPER_H
#define __STEPPER_H

#include "Arduino.h"

#define MIN_DELAY 10
#define MAX_DELAY 100

#define __LINEAR_RAMP
//#define __EXPONENTIAL_RAMP

class Stepper
{
private:
  uint8_t PUL, DIR, ENA;
  uint16_t stepsPerRotation;
  int currentStep;

public:
  Stepper(uint8_t pul, uint8_t dir, uint8_t ena, uint16_t steps);
  void Setup();
  void Tick();
  void RotateTo(float fraction);
};

#endif // __STEPPER_H
