#pragma once

/*
Timer 1 en mode CTC avec prescaler modifiable mais par défaut a 1024
*/

#include <avr/io.h> 
#include <avr/interrupt.h>

class timer
{
public:
    timer();
    ~timer(){};
    void startTimer(uint16_t time);
    void stopTimer();
    void setPrescaler(uint16_t);
private:
    uint16_t _prescaler = 1024;
};