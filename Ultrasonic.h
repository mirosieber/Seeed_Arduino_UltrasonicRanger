#ifndef Ultrasonic_H
#define Ultrasonic_H

#include "Arduino.h"
#include "PulseInInterrupt.h"

class Ultrasonic {
  public:
    Ultrasonic();
    void init(int pin);
    void startMeasurement();
    long getInCentimeters();
    long getInMillimeters();
    long getInInches();
  private:
    int _pin;
    long lastDuration;
    PulseInInterrupt pulseSensor;
};

#endif
