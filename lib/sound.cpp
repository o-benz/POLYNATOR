#include "sound.h"

sound::sound()
{
    DDRD |= (1<<PD6) | (1<<PD7);
    TCNT2=0;
    TCCR2A |= (1 << COM2A0) | (1 << WGM21);
    TCCR2B |= (1 << CS22) | (1 << CS20); 
}

void sound::playNote(uint16_t note)
{
    TCNT2=0;
    OCR2A = 8000000 / (2 * 1024 * tabNotes[note-45]) - 1;
}

void sound::stopSound()
{
    TCNT2=0;
    DDRD=0;
    TCCR2A=0;
    TCCR2B=0;
    OCR2A=0;
}