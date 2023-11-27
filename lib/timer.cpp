#include "timer.h"

timer::timer()
{
    cli ();
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);
    sei ();
}

void timer::setPrescaler(uint16_t prescaler)
{
    _prescaler = prescaler;
}

void timer::startTimer(uint16_t time)
{
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0 ;
    OCR1A = time;
    switch (_prescaler)
    {
        case 1024:
            TCCR1B = (1 << WGM12)|(1 << CS10)|(1 << CS12);
            break;
        case 256:
            TCCR1B = (1 << WGM12)|(1 << CS12);
            break;
        case 64:
            TCCR1B = (1 << WGM12)|(1 << CS10)|(1 << CS11);
            break;
        case 8:
            TCCR1B = (1 << WGM12)|(1 << CS11);
            break;
        case 1:
            TCCR1B = (1 << WGM12)|(1 << CS10);
            break;
        default:
            TCCR1B = (1 << WGM12)|(1 << CS10)|(1 << CS12);
            break;
    }
    TCCR1A = (1 << COM1A1)|(1 << COM1A0);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
}

void timer::stopTimer()
{
    TCCR1B = 0;
}