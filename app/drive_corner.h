#ifndef DRIVE_CORNER
#define DRIVE_CORNER

#define SPEED_WHEELS_LEFT 140
#define SPEED_WHEELS_RIGHT 125
#define ROTATE_SPEED_LEFT 80
#define ROTATE_SPEED_RIGHT 75

#define ROTATION_AXE 800

#define IMPULSION_ROTATION 100
#define IMPULSION_DRIVE 50
#define DELAY_ERROR 30
#define DELAY_ERROR_2 190
#define WAIT 500

#include "exec.h"

uint8_t sensor = 0;

void turnCorner(bool isTurnLeft)
{
    robotExec.driveRatio(180,180,!isTurnLeft,isTurnLeft);
    _delay_ms(IMPULSION_ROTATION);
    robotExec.driveRatio(ROTATE_SPEED_LEFT,ROTATE_SPEED_RIGHT,!isTurnLeft,isTurnLeft);
    while (!(sensor &= 0x04))
    {
        sensor = robotExec.readSensor();
        _delay_ms(DELAY_ERROR);
    }
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
}

bool driveCorner(uint8_t& intersectionNumber, bool& isLine)
{
    uint8_t lineCounter = 0;
    bool isDriveLine = true;
    bool isTurnLeft = false;
    bool passIntersection = false;

    robotExec.driveRatio(255,255);
    _delay_ms(IMPULSION_DRIVE);
    while(isDriveLine)
    {
        sensor = robotExec.readSensor();
        switch (sensor)
        {
        case 0x04:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x04)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x06:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x06)
            {
                break;
            }
            passIntersection = false;
            break;
        
        case 0x03:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x03)
            {
                break;
            }
            passIntersection = false;
            break;
        
        case 0x01:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x01)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x02:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x02)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x0C:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x0C)
            {
                break;
            }
            passIntersection = false;
            break;
        
        case 0x18:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x18)
            {
                break;
            }
            passIntersection = false;
            break;
        
        case 0x10:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x10)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x08:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x08)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x0F:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x0F)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            isTurnLeft = true;
            lineCounter++;
            passIntersection = true;
            break;

        case 0x07:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x07)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            isTurnLeft = true;
            lineCounter++;
            passIntersection = true;
            break;
        
        case 0x1C:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x1C)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            lineCounter++;
            passIntersection = true;
            break;
        
        case 0x1E:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x1E)
            {
                break;
            }
            _delay_ms(190);
            lineCounter++;
            passIntersection = true;
            break;
        
        case 0x1F:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x1F)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            lineCounter++;
            passIntersection = true;
            break;
        
        case 0x00:
            _delay_ms(DELAY_ERROR);
            if(robotExec.readSensor() == 0x00)
            {
                if(!passIntersection)
                {
                    isLine = false;
                }
                isDriveLine = false;
                break;
            }
            break;

        default:
            break;
        }
    }
    robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-10);
    _delay_ms(ROTATION_AXE);
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    turnCorner(isTurnLeft);

    intersectionNumber = lineCounter;
    isDriveLine = true;
    robotExec.driveRatio(255,255);
    _delay_ms(DELAY_ERROR);
    while(isDriveLine)
    {
        sensor = robotExec.readSensor();
        switch (sensor)
        {
        case 0x04:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            break;

        case 0x06:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            break;
        
        case 0x03:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            break;
        
        case 0x01:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            break;

        case 0x02:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            break;

        case 0x0C:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            break;
        
        case 0x18:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            break;
        
        case 0x10:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            break;
        
        case 0x00:
            _delay_ms(DELAY_ERROR);
            if(robotExec.readSensor() == 0x00)
            {
                isDriveLine = false;
                break;
            }
        default:
            break;
        }
    }
    robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
    _delay_ms(ROTATION_AXE);
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    return isTurnLeft;
}

#endif