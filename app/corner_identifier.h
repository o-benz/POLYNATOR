#ifndef CORNER_IDENTIFIER_H
#define CORNER_IDENTIFIER_H

#define DELAY_BUTTON 30
#define ONE_SEC_DELAY 1000
#define TWO_SEC_DELAY 2000
#define PERIOD 126 // F_CPU/1024/25/2

#include "drive_corner.h"
#include "lcm_so1602dtr_m.h"
#include "customprocs.h"
#include "lcm_so1602dtr_m_fw.h"

#define DEMO_DDR   DDRC
#define DEMO_PORT    PORTC   

void static inline wCorner(void)
{
    cp_wait_ms(50);
}

void corner_identify()
{
    LCM disp(&DEMO_DDR, &DEMO_PORT); 
    uint8_t firstInt = 0;
    uint8_t secondInt = 0;
    bool isTurnLeft = false;
    bool isLine = true;
    robotExec.setDark();
    _delay_ms(TWO_SEC_DELAY);

    robotExec.startTimer(PERIOD);

    isTurnLeft = driveCorner(firstInt, isLine);
    turnCorner(isTurnLeft);
    isTurnLeft = driveCorner(secondInt, isLine);
    turnCorner(isTurnLeft);

    disp.clear();
    if(firstInt == 2 && secondInt == 1)
    {
        if(isLine)
        {
            disp.write("(1, 1)", 0);
            wCorner();
            disp.write("EST", 16);
            wCorner();
        }
        else
        {
            disp.write("(1, 7)", 0);
            wCorner();
            disp.write("SUD", 16);
            wCorner();
        }
    }
    else if(firstInt == 1 && secondInt == 2)
    {
        if(isLine)
        {
            disp.write("(1, 1)", 0);
            wCorner();
            disp.write("SUD", 16);
            wCorner();
        }
        else
        {
            disp.write("(1, 7)", 0);
            wCorner();
            disp.write("OUEST", 16);
            wCorner();
        }
    }
    else if(firstInt == 1 && secondInt == 1 && isTurnLeft)
    {
        disp.write("(4, 1)", 0);
        wCorner();
        disp.write("EST", 16);
        wCorner();
    }
    else if(firstInt == 1 && secondInt == 1 && !isTurnLeft)
    {
        disp.write("(4, 1)", 0);
        wCorner();
        disp.write("NORD", 16);
        wCorner();
    }
    else if(firstInt == 3 && secondInt == 2)
    {
        disp.write("(4, 7)", 0);
        wCorner();
        disp.write("OUEST", 16);
        wCorner();
    }
    else if(firstInt == 2 && secondInt == 3)
    {
        disp.write("(4, 7)", 0);
        wCorner();
        disp.write("NORD", 16);
        wCorner();
    }
    robotExec.stopTimer();
    robotExec.playNote(4);
    robotExec.setGreen();
    _delay_ms(ONE_SEC_DELAY);
    robotExec.stopSound();
    return;
}

#endif