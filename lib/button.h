#pragma once

#define DELAY_BUTTON 30

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class button
{
public:
    button();
    ~button(){};
};

// ISR POUR LES BOUTONS

// volatile bool gIsSelectionPressed = false;
// volatile bool gIsValidationPressed = false;
// volatile bool gIsInterruptPressed = false;

// ISR(INT0_vect) 
// {
//     _delay_ms(BUTTON_DEBOUNCE_DELAY);
//     gIsInterruptPressed = true;
//     EIFR |= (1 << INTF0);
// }

// ISR(INT1_vect) 
// {
//     _delay_ms(BUTTON_DEBOUNCE_DELAY);
//     gIsValidationPressed = true;
//     EIFR |= (1 << INTF1);
// }

// ISR(INT2_vect) 
// {
//     _delay_ms(BUTTON_DEBOUNCE_DELAY);
//     gIsSelectionPressed = true;
//     EIFR |= (1 << INTF2);
// }