#pragma once

/*
Led branchée sur les pins A6 et A7 par défaut.
*/ 
#define DELAY_FOR_AMBER 10
#define DDR_LED DDRA
#define PORT_LED PORTA

#include <avr/io.h> 
#include <util/delay.h>

class led
{
public:
    led();
    ~led(){};
    void setGreen();
    void setRed();
    void setAmber();
    void setDark(); 

private:
    uint8_t red = (1<<PORTA6);
    uint8_t green = (1<<PORTA7);
    uint8_t mask = red | green;
};