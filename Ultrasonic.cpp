#include "Ultrasonic.h"

Ultrasonic::Ultrasonic() : lastDuration(0) {}

void Ultrasonic::init(int pin) {
    _pin = pin;
    pulseSensor.init(pin);
}

void Ultrasonic::startMeasurement() {
    noInterrupts();
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_pin, LOW);
    pinMode(_pin, INPUT);
    interrupts();
    pulseSensor.begin();
}

long Ultrasonic::getInCentimeters() {
    unsigned long duration = pulseSensor.getPulseDuration();
    if (duration > 0) {
        lastDuration = duration;
    }
    return lastDuration / 58; // Simplified from /29/2
}

long Ultrasonic::getInMillimeters() {
    unsigned long duration = pulseSensor.getPulseDuration();
    if (duration > 0) {
        lastDuration = duration;
    }
    return (lastDuration * 10) / 58; // Simplified from *5/29
}

long Ultrasonic::getInInches() {
    unsigned long duration = pulseSensor.getPulseDuration();
    if (duration > 0) {
        lastDuration = duration;
    }
    return lastDuration / 148; // Simplified from /74/2
}
