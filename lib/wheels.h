/*
Roue gauche branchée sur les pins B4 et B5, roue droite branchée sur les pins B1 et B3
*/

#include <avr/io.h>

class wheels
{
public:
    wheels();
    ~wheels(){};
    void driveRatio(uint8_t leftRatio, uint8_t rightRatio, bool leftIsDrive = true, bool rightIsDrive = true);
};
