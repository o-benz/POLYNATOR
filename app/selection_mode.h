#include "path_traveller.h"
#include "corner_identifier.h"

volatile bool gIsInterruptPressed = false;

ISR(INT0_vect) 
{
    _delay_ms(BUTTON_DEBOUNCE_DELAY);
    gIsInterruptPressed = true;
    EIFR |= (1 << INTF0);
}

void selection()
{
    while(true)
    {
        if(gIsInterruptPressed)
        {
            gIsInterruptPressed = false;
            corner_identify();
            break;
        }
        if(gIsSelectionPressed)
        {
            path_travel();
            gIsSelectionPressed = false;
            break;
        }
    }
    return;
}