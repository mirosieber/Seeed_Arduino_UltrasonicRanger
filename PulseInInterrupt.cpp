#include "PulseInInterrupt.h"
#include <driver/gpio.h>

bool PulseInInterrupt::_isrServiceInstalled = false;

PulseInInterrupt::PulseInInterrupt() 
    : _pin(255), _pulseStart(0), _pulseEnd(0), _pulseComplete(false), _waitingForStart(true) {}

PulseInInterrupt::~PulseInInterrupt() {
    if (_pin != 255) {
        gpio_isr_handler_remove(static_cast<gpio_num_t>(_pin));
        pinMode(_pin, INPUT);
    }
}

void PulseInInterrupt::init(uint8_t pin) {
    if (_pin != 255) {
        gpio_isr_handler_remove(static_cast<gpio_num_t>(_pin));
    }

    _pin = pin;
    pinMode(_pin, INPUT);

    if (!_isrServiceInstalled) {
        gpio_install_isr_service(0);
        _isrServiceInstalled = true;
    }

    gpio_set_intr_type(static_cast<gpio_num_t>(_pin), GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(static_cast<gpio_num_t>(_pin), isrHandler, this);
}

void PulseInInterrupt::begin() {
    _pulseComplete = false;
    _waitingForStart = true;
}

void IRAM_ATTR PulseInInterrupt::isrHandler(void* arg) {
    PulseInInterrupt* instance = static_cast<PulseInInterrupt*>(arg);
    if (instance) {
        instance->handleInterrupt();
    }
}

void PulseInInterrupt::handleInterrupt() {
    int state = digitalRead(_pin);
    if (state == HIGH && _waitingForStart) {
        _pulseStart = micros();
        _waitingForStart = false;
        gpio_set_intr_type(static_cast<gpio_num_t>(_pin), GPIO_INTR_NEGEDGE);
    } else if (state == LOW && !_waitingForStart) {
        _pulseEnd = micros();
        _pulseComplete = true;
        _waitingForStart = true;
        gpio_set_intr_type(static_cast<gpio_num_t>(_pin), GPIO_INTR_POSEDGE);
    }
}

unsigned long PulseInInterrupt::getPulseDuration() {
    if (_pulseComplete) {
        unsigned long duration = _pulseEnd - _pulseStart;
        _pulseComplete = false;
        return duration;
    }
    return 0;
}
