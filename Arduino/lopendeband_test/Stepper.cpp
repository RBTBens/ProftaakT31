#include "Stepper.h"

Stepper::Stepper(uint8_t pul, uint8_t dir, uint8_t ena, uint16_t steps)
{
  PUL = pul;
  DIR = dir;
  ENA = ena;

  stepsPerRotation = steps;
  currentStep = 0;
}

void Stepper::Setup()
{
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void Stepper::Tick()
{
  // To-Do
}

void Stepper::RotateTo(float fraction)
{
  uint16_t targetStep = (uint16_t)(fraction * stepsPerRotation);
  int16_t steps = targetStep - currentStep;  
  currentStep += steps;

  if (steps <= -3200)
  {
    steps += stepsPerRotation;
  }
  else if (steps >= 3200)
  {
    steps -= stepsPerRotation;
  }

  digitalWrite(DIR, steps > 0 ? LOW : HIGH);
  digitalWrite(ENA, HIGH);

  for (int i = 0; i < abs(steps); i++)
  {
    float x = (PI / abs(steps)) * i;
    unsigned int d = MAX_DELAY - (MAX_DELAY - MIN_DELAY) * sin(x);
    
    digitalWrite(PUL, HIGH);
    delayMicroseconds(d);
    digitalWrite(PUL, LOW);
    delayMicroseconds(d);
  }
}

