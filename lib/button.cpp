#include "button.h"

button::button()
{
    cli ();
    DDRB &= ~(1<<PB2); // Selection
    DDRD &= ~(1<<DDD3); // Validation
    DDRD &= ~(1<<DDD2); // Interrupt
    EIMSK |= (1 << INT0)|(1 << INT1)|(1 << INT2);
    EICRA |= (1 << ISC01)|(1 << ISC11)|(1 << ISC21);
    sei ();
}
