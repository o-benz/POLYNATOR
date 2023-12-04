#pragma once

#include <avr/io.h>

class lineFollower {
public:
    lineFollower();
    void initSensorPins();
    uint8_t readSensors();

private:
    bool readDigitalPin(uint8_t pin);

};
