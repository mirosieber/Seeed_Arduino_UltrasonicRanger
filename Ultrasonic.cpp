/*
    Ultrasonic.cpp
    A library for ultrasonic ranger

    Copyright (c) 2012 seeed technology inc.
    Website    : www.seeed.cc
    Author     : LG, FrankieChu
    Create Time: Jan 17,2013
    Change Log :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"
#include "Ultrasonic.h"


Ultrasonic::Ultrasonic() {
}

void Ultrasonic::init(int pin){
    _pin = pin;
    pulseSensor.begin(pin);     // Initialisiert Interrupt
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
    pulseSensor.begin(_pin);
}

/*The measured distance from the range 0 to 400 Centimeters*/
long Ultrasonic::getInCentimeters() {
    unsigned long duration = pulseSensor.getPulseDuration();
    if (duration > 0) {
        lastDuration = duration;
    }
    long RangeInCentimeters;
    RangeInCentimeters = lastDuration / 29 / 2;
    return RangeInCentimeters;
}

/*The measured distance from the range 0 to 4000 Millimeters*/
long Ultrasonic::getInMillimeters() {
    unsigned long duration = pulseSensor.getPulseDuration();
    if (duration > 0) {
        lastDuration = duration;
    }
    long RangeInMillimeters;
    RangeInMillimeters = lastDuration * (10 / 2) / 29;
    return RangeInMillimeters;
}

/*The measured distance from the range 0 to 157 Inches*/
long Ultrasonic::getInInches() {
    unsigned long duration = pulseSensor.getPulseDuration();
    if (duration > 0) {
        lastDuration = duration;
    }
    long RangeInInches;
    RangeInInches = lastDuration / 74 / 2;
    return RangeInInches;
}
