#include "obstacleDetector.h"
#include <avr/io.h>

obstacleDetector::obstacleDetector()
{
    initADC();
}

void obstacleDetector::initADC() {
    // Configuration de l'ADC
    DDRA &= ~(1 << distanceSensorPin);
    ADMUX |= (1 << REFS0); // Utiliser AVCC comme référence de tension
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Activer l'ADC et définir la fréquence de l'horloge
}

bool obstacleDetector::analogRead(const uint8_t pin) {
    // Sélectionner le canal ADC et démarrer la conversion
    ADMUX = (ADMUX & 0xF8) | (pin & 0x07);
    ADCSRA |= (1 << ADSC);

    // Lire la valeur convertie
    uint16_t convertedValue = (ADCL) | (ADCH << 8);
    // Retourner true si la valeur convertie est supérieure au seuil
    return convertedValue > SEUIL_OBSTACLE;
}

bool obstacleDetector::detect() 
{
    initADC();
    return analogRead(distanceSensorPin);
}
