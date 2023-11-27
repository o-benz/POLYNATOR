#ifndef DRIVE_CORNER
#define DRIVE_CORNER

#define SPEED_WHEELS 140
#define ROTATE_SPEED 80
#define DELAY_ERROR 30

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "robot.h"

class robot robotDrive;
uint8_t sensor = 0;

void driveLine(uint8_t intersectionNumber = 10, bool isLeftIntersection = true)
{
    uint8_t rightLineCounter = 0;
    uint8_t leftLineCounter = 0;
    bool isDriveLine = true;
    uint8_t leftIntersectionNumber = 10;
    uint8_t rightIntersectionNumber = 10;

    if (isLeftIntersection)
    {
        leftIntersectionNumber = intersectionNumber;
    }
    else
    {
        rightIntersectionNumber = intersectionNumber;
    }
    robotDrive.driveRatio(255,255);
    _delay_ms(30);
    while(isDriveLine && leftLineCounter < leftIntersectionNumber && rightLineCounter < rightIntersectionNumber)
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

        case 0x08:
            robotDrive.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            break;

        case 0x0F:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x0F)
            {
                break;
            }
            _delay_ms(190);
            rightLineCounter++;
            break;

        case 0x07:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x07)
            {
                break;
            }
            _delay_ms(190);
            rightLineCounter++;
            break;
        
        case 0x1C:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x1C)
            {
                break;
            }
            _delay_ms(190);
            leftLineCounter++;
            break;
        
        case 0x1E:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotDrive.readSensor() != 0x1E)
            {
                break;
            }
            _delay_ms(190);
            leftLineCounter++;
            break;
        
        case 0x1F:
            robotDrive.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(200);
            leftLineCounter++;
            rightLineCounter++;
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
    _delay_ms(1000);
    robotDrive.driveRatio(0,0);
    return;
}

void turnRight(uint8_t intersectionNumber = 1)
{
    uint8_t crossedInteserction = 0;
    robotDrive.driveRatio(255,255,true,false);
    _delay_ms(200);
    robotDrive.driveRatio(ROTATE_SPEED,ROTATE_SPEED,true,false);
    while (crossedInteserction < intersectionNumber)
    {
        sensor = robotDrive.readSensor();
        if (sensor == 0x06)
        {
            crossedInteserction++;
        }
        _delay_ms(100);
    }
    robotDrive.driveRatio(0,0);
}

void turnLeft(uint8_t intersectionNumber = 1)
{
    uint8_t crossedInteserction = 0;
    robotDrive.driveRatio(255,255,false,true);
    _delay_ms(200);
    robotDrive.driveRatio(ROTATE_SPEED-5,ROTATE_SPEED-5,false,true);
    while (crossedInteserction < intersectionNumber)
    {
        sensor = robotDrive.readSensor();
        if (sensor == 0x0C)
        {
            crossedInteserction++;
        }
        if (crossedInteserction < intersectionNumber)
        {
            _delay_ms(100);
        }
    }
    robotDrive.driveRatio(0,0);
}

#endif