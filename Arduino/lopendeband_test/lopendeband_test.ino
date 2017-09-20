#include "Stepper.h"

// Stepper motor controller pins
#define PUL 7
#define DIR 6
#define ENA 5
#define STEPS 6400 // max is 6400

// Containers
#define CONTAINER1 0.25
#define CONTAINER2 0.50
#define CONTAINER3 0.75
#define START_POINT 1.00

// Timings
#define ONE_SECOND_TICKS 15624
#define TEN_MILLIS 156


Stepper* stepper = new Stepper(PUL, DIR, ENA, STEPS);
int microDelay = 100;
float offsets[3] = { CONTAINER1, CONTAINER2, CONTAINER3 };

void setup()
{
  Serial.begin(250000);
  stepper->Setup();
  stepper->RotateTo(START_POINT);
  
//  cli();
//  TCCR1A = 0;
//  TCCR1B = 0;
//  TCNT1 = 0;
//
//  OCR1A = TEN_MILLIS;
//  TCCR1B |= _BV(WGM12);
//  TCCR1B |= _BV(CS10);
//  TIMSK1 |= _BV(OCIE1A);
//  sei();
}

void loop()
{
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    c -= 49;
    if (c < 0 || c > 2)
    {
      return;
    }
    
    float frac = offsets[c];
    stepper->RotateTo(frac);
    Serial.print("Rotated to ");
    Serial.println(frac);
    stepper->RotateTo(START_POINT);
    Serial.println("Rotated to start");
  }
}

//ISR(TIMER1_COMPA_vect)
//{
//  
//}

