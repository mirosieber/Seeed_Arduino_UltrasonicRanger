#ifndef PULSE_IN_INTERRUPT_H
#define PULSE_IN_INTERRUPT_H

#include <Arduino.h>

class PulseInInterrupt {
public:
    PulseInInterrupt();

    void init(uint8_t pin);
    void begin();
    unsigned long getPulseDuration();

private:
    static void isrWrapper();
    void handleInterrupt();

    uint8_t _pin;
    static volatile unsigned long _pulseStart;
    static volatile unsigned long _pulseEnd;
    static volatile bool _pulseComplete;
    static volatile bool _waitingForStart;
    static PulseInInterrupt* _instance;
};

#endif // PULSE_IN_INTERRUPT_H
