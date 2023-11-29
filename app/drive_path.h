#ifndef DRIVE_PATH
#define DRIVE_PATH

#define SPEED_WHEELS 140 //140
#define ROTATE_SPEED 80 //80
#define DELAY_ERROR 30
#define DELAY_180 2000
#define ROTATION_AXE 800
#define PULSE 30
#define ROTATE_MARGE 150
#define WAIT 500
#define DELAY_ERROR_2 190
#define DELAY_ROTATE 100
#define PUSH_ROTATE_180 200


#define DELAY_TIMER 12000 // 14000


#include "exec.h"

uint8_t sensorPath = 0;

bool gExpiredTimer = false;

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
    robotExec.driveRatio(255,255);
    gExpiredTimer = false;
    robotExec.startTimer(DELAY_TIMER);
    _delay_ms(PULSE);
    while(isDriveLine && leftLineCounter < leftIntersectionNumber && rightLineCounter < rightIntersectionNumber && !gExpiredTimer)
    {
        sensorPath = robotExec.readSensor();
        switch (sensorPath)
        {
        case 0x04:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            break;

        case 0x06:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            break;
        
        case 0x03:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            break;
        
        case 0x01:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            break;

        case 0x02:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS-30);
            break;

        case 0x0C:
            robotExec.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            break;
        
        case 0x18:
            robotExec.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            break;
        
        case 0x10:
            robotExec.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            break;

        case 0x08:
            robotExec.driveRatio(SPEED_WHEELS-30,SPEED_WHEELS);
            break;

        case 0x0F:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x0F)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            rightLineCounter++;
            break;

        case 0x07:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x07)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            rightLineCounter++;
            break;
        
        case 0x1C:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x1C)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            leftLineCounter++;
            break;
        
        case 0x1E:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x1E)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            leftLineCounter++;
            break;
        
        case 0x1F:
            robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
            _delay_ms(DELAY_ERROR_2);
            leftLineCounter++;
            rightLineCounter++;
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
    robotExec.stopTimer();
    robotExec.driveRatio(SPEED_WHEELS,SPEED_WHEELS);
    _delay_ms(ROTATION_AXE);
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    return;
}

void turnRight(uint8_t intersectionNumber = 1)
{
    uint8_t crossedInteserction = 0;
    robotExec.driveRatio(255,255,true,false);
    _delay_ms(ROTATE_MARGE);
    robotExec.driveRatio(ROTATE_SPEED,ROTATE_SPEED,true,false);
    while (crossedInteserction < intersectionNumber)
    {
        sensorPath = robotExec.readSensor();
        if (sensorPath == 0x06)
        {
            crossedInteserction++;
        }
        _delay_ms(DELAY_ROTATE);
    }
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    return;
}

void turnLeft(uint8_t intersectionNumber = 1)
{
    uint8_t crossedInteserction = 0;
    robotExec.driveRatio(255,255,false,true);
    _delay_ms(ROTATE_MARGE);
    robotExec.driveRatio(ROTATE_SPEED-5,ROTATE_SPEED-5,false,true);
    while (crossedInteserction < intersectionNumber)
    {
        sensorPath = robotExec.readSensor();
        if (sensorPath == 0x0C)
        {
            crossedInteserction++;
        }
        if (crossedInteserction < intersectionNumber)
        {
            _delay_ms(DELAY_ROTATE);
        }
    }
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    return;
}

void turn180()
{
    robotExec.driveRatio(255,255,false,true);
    _delay_ms(PUSH_ROTATE_180);
    robotExec.driveRatio(ROTATE_SPEED,ROTATE_SPEED,false,true);
    _delay_ms(DELAY_180);
    sensorPath = robotExec.readSensor();
    while(!(sensorPath &= 0x04))
    {  
        sensorPath = robotExec.readSensor();
    }
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    return;
}

#endif