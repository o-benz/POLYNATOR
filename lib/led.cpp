#include "led.h"

led::led()
{
    DDR_LED |= mask;
}

void led::setRed()
{
  PORT_LED &= ~green;
  PORT_LED |= red;
}

void led::setGreen()
{
  PORT_LED &= ~red;
  PORT_LED |= green;
}

void led::setDark()
{
  PORT_LED &= ~red;
  PORT_LED &= ~green;
}

void led::setAmber()
{
    setRed();
    _delay_ms(DELAY_FOR_AMBER); 
    setGreen();
    _delay_ms(DELAY_FOR_AMBER);
}