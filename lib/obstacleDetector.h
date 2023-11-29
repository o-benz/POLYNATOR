#ifndef OBSTACLEDETECTOR_H
#define OBSTACLEDETECTOR_H

#include <stdint.h>
#include <avr/io.h>

class obstacleDetector {
public:
    // Constructeur
    obstacleDetector();

    // Initialiser l'ADC
    void initADC();

    // Détecter la présence d'un obstacle
    bool detect();

private:
    // Lire une valeur analogique et déterminer si elle est en dessous du seuil
    bool analogRead(const uint8_t);

    // Numéro de pin du capteur
    uint8_t distanceSensorPin = PA5;

    // Seuil de détection d'obstacle
    uint16_t SEUIL_OBSTACLE = 220;
};

#endif // OBSTACLEDETECTOR_H

