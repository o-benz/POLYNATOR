#include "path_traveller.h"
#include "corner_identifier.h"

volatile bool gIsInterruptPressed = false;
volatile bool isGreen = false;
extern bool gExpiredTimer;
volatile bool isCorner;

ISR(TIMER1_COMPA_vect) 
{
    if(!isGreen && isCorner)
    {
        robotExec.setGreen();
    }
    else if (isGreen && isCorner)
    {
        robotExec.setDark();
    }
    isGreen = !isGreen;
    gExpiredTimer = true;
}

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
            isCorner = true;
            corner_identify();
            break;
        }
        if(gIsSelectionPressed)
        {
            isCorner = false;
            gIsSelectionPressed = false;
            path_travel();
            break;
        }
    }
    return;
}