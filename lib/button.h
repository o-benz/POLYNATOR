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