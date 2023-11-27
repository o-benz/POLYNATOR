#include <avr/io.h>
#include "lineFollower.h"

lineFollower::lineFollower() {
    initSensorPins();
}

void lineFollower::initSensorPins() {
    // Configurer chaque pin comme entrée
    DDRA &= ~(1 << PA0);  // Configuration de PA0 comme entrée
    DDRA &= ~(1 << PA1);  // Configuration de PA1 comme entrée
    DDRA &= ~(1 << PA2);  // Configuration de PA2 comme entrée
    DDRA &= ~(1 << PA3);  // Configuration de PA3 comme entrée
    DDRA &= ~(1 << PA4);  // Configuration de PA4 comme entrée
}

bool lineFollower::readDigitalPin(uint8_t pin) {
    return PINA & (1 << pin);  // Lire l'état du pin spécifié
}

uint8_t lineFollower::readSensors() {
    uint8_t sensorState = 0x00;
    sensorState |= (readDigitalPin(PA0) << 4);  
    sensorState |= (readDigitalPin(PA1) << 3);  // Lecture de PA1 et décalage à la position 3
    sensorState |= (readDigitalPin(PA2) << 2);  // Lecture de PA2 et décalage à la position 2
    sensorState |= (readDigitalPin(PA3) << 1);  // Lecture de PA3 et décalage à la position 1
    sensorState |= readDigitalPin(PA4);         // Lecture de PA4
    return sensorState;  // Retourner l'état des capteurs dans un octet
}
