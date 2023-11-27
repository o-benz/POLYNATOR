#ifndef DRIVE_CORNER
#define DRIVE_CORNER

#define SPEED_WHEELS 140
#define ROTATE_SPEED 80

#define ROTATION_AXE 1000

#define IMPULSION_ROTATION 150
#define IMPULSION_DRIVE 50
#define DELAY_ERROR 30
#define DELAY_ERROR_2 190
#define WAIT 500

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "robot.h"

class robot robotDrive;
uint8_t sensor = 0;

void turnCorner(bool isTurnLeft)
{
    robotDrive.driveRatio(180,180,!isTurnLeft,isTurnLeft);
    _delay_ms(IMPULSION_ROTATION);
    robotDrive.driveRatio(ROTATE_SPEED,ROTATE_SPEED,!isTurnLeft,isTurnLeft);
    while (sensor != 0x06)
    {
        sensor = robotDrive.readSensor();
        _delay_ms(DELAY_ERROR);
    }
    robotDrive.driveRatio(0,0);
    _delay_ms(WAIT);
}

bool driveCorner(uint8_t& intersectionNumber, bool& isLine)
{
    uint8_t lineCounter = 0;
    bool isDriveLine = true;
    bool isTurnLeft = false;
    bool passIntersection = false;

    robotDrive.driveRatio(255,255);
    _delay_ms(IMPULSION_DRIVE);
    while(isDriveLine)
    {
        sensor = robotDrive.readSensor();
        switch (sensor)
        {
        case 0x04:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x04)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x06:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x06)
            {
                break;
            }
            passIntersection = false;
            break;
        
        case 0x03:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x03)
            {
                break;
            }
            passIntersection = false;
            break;
        
        case 0x01:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x01)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x02:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x02)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x0C:
            robotDrive.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x0C)
            {
                break;
            }
            passIntersection = false;
            break;
        
        case 0x18:
            robotDrive.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x18)
            {
                break;
            }
            passIntersection = false;
            break;
        
        case 0x10:
            robotDrive.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x10)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x08:
            robotDrive.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x08)
            {
                break;
            }
            passIntersection = false;
            break;

        case 0x0F:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x0F)
            {
                break;
            }
            _delay_ms(190);
            isTurnLeft = true;
            lineCounter++;
            passIntersection = true;
            break;

        case 0x07:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x07)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            isTurnLeft = true;
            lineCounter++;
            passIntersection = true;
            break;
        
        case 0x1C:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x1C)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            lineCounter++;
            passIntersection = true;
            break;
        
        case 0x1E:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x1E)
            {
                break;
            }
            _delay_ms(190);
            lineCounter++;
            passIntersection = true;
            break;
        
        case 0x1F:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x1F)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            lineCounter++;
            passIntersection = true;
            break;
        
        case 0x00:
            _delay_ms(DELAY_ERROR);
            if(robotDrive.readSensor() == 0x00)
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
    robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
    _delay_ms(ROTATION_AXE);
    robotDrive.driveRatio(0,0);
    _delay_ms(WAIT);
    turnCorner(isTurnLeft);

    intersectionNumber = lineCounter;
    isDriveLine = true;
    robotDrive.driveRatio(255,255);
    _delay_ms(DELAY_ERROR);
    while(isDriveLine)
    {
        sensor = robotDrive.readSensor();
        switch (sensor)
        {
        case 0x04:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            break;

        case 0x06:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            break;
        
        case 0x03:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            break;
        
        case 0x01:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            break;

        case 0x02:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            break;

        case 0x0C:
            robotDrive.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            break;
        
        case 0x18:
            robotDrive.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            break;
        
        case 0x10:
            robotDrive.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            break;
        
        case 0x00:
            _delay_ms(DELAY_ERROR);
            if(robotDrive.readSensor() == 0x00)
            {
                isDriveLine = false;
                break;
            }
        default:
            break;
        }
    }
    robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
    _delay_ms(ROTATION_AXE);
    robotDrive.driveRatio(0,0);
    _delay_ms(WAIT);
    return isTurnLeft;
}

#endif