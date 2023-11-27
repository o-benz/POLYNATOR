#include "wheels.h"

wheels::wheels()
{
    DDRB |= (1 << PB3)|(1 << PB4)|(1 << PB1)|(1 << PB5);

    TCNT0 = 0;
    TCCR0A = (1 << COM0A1)|(0 << COM0A0)|(1 << COM0B1)|(0 << COM0B0)|(1 << WGM00)|(0 << WGM01);
    TCCR0B = (0 << CS00)|(1 << CS01)|(0 << CS02)|(0 << WGM02);
    OCR0A = 0;
    OCR0B = 0;
}

void wheels::driveRatio(uint8_t leftRatio, uint8_t rightRatio, bool leftIsDrive, bool rightIsDrive)
{
    if (leftIsDrive)
    {
        PORTB &= ~(1 << PORTB5);
    }
    else
    {
        PORTB |= (1 << PORTB5);
    }
    if (rightIsDrive)
    {
        PORTB &= ~(1 << PORTB1);
    }
    else
    {
        PORTB |= (1 << PORTB1);
    }
    OCR0A = rightRatio;
    OCR0B = leftRatio;
}