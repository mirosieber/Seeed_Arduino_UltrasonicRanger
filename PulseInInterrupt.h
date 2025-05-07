#ifndef PULSE_IN_INTERRUPT_H
#define PULSE_IN_INTERRUPT_H

#include <Arduino.h>
#include <driver/gpio.h>

class PulseInInterrupt {
public:
    PulseInInterrupt();
    ~PulseInInterrupt();

    void init(uint8_t pin);
    void begin();
    unsigned long getPulseDuration();

private:
    static void IRAM_ATTR isrHandler(void* arg);
    void handleInterrupt();

    uint8_t _pin;
    volatile unsigned long _pulseStart;
    volatile unsigned long _pulseEnd;
    volatile bool _pulseComplete;
    volatile bool _waitingForStart;
    static bool _isrServiceInstalled;
};

#endif
