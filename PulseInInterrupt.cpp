#include "PulseInInterrupt.h"

volatile unsigned long PulseInInterrupt::_pulseStart = 0;
volatile unsigned long PulseInInterrupt::_pulseEnd = 0;
volatile bool PulseInInterrupt::_pulseComplete = false;
volatile bool PulseInInterrupt::_waitingForStart = true;
PulseInInterrupt* PulseInInterrupt::_instance = nullptr;

PulseInInterrupt::PulseInInterrupt(uint8_t pin) : _pin(pin) {}

void PulseInInterrupt::begin() {
    pinMode(_pin, INPUT);
    _instance = this;
    attachInterrupt(digitalPinToInterrupt(_pin), isrWrapper, RISING);
}

void PulseInInterrupt::isrWrapper() {
    if (_instance) {
        _instance->handleInterrupt();
    }
}

void PulseInInterrupt::handleInterrupt() {
    if (_waitingForStart) {
        _pulseStart = micros();
        _waitingForStart = false;
        attachInterrupt(digitalPinToInterrupt(_pin), isrWrapper, FALLING);
    } else {
        _pulseEnd = micros();
        _pulseComplete = true;
        _waitingForStart = true;
        attachInterrupt(digitalPinToInterrupt(_pin), isrWrapper, RISING);
    }
}

unsigned long PulseInInterrupt::getPulseDuration() {
    if (_pulseComplete) {
        _pulseComplete = false;
        return _pulseEnd - _pulseStart;
    }
    return 0;
}
