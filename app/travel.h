#ifndef TRAVEL
#define TRAVEL

#define DELAY_SOUND 200
#define DELAY_STOP_SOUND 100
#define DELAY_SOUND_OBSTACLE 2000
#define NOTE_OBSTACLE 35
#define NOTE_FINISH 4
#define TIMER 200

#include "shortest_path_algo.h"
#include "drive_path.h"

enum orientation
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

uint8_t calculPoint(uint8_t x, uint8_t y)
{
    return (((x-1)*7)+y-1);
}


volatile orientation orientationMemory = SOUTH;

uint8_t doTravelPoint(uint8_t endPoint, uint8_t startPoint = 0)
{
    uint8_t* path = shortestPath(startPoint, endPoint);
  
    uint8_t curPos = path[0];
    uint8_t counter = 1;
    uint8_t nextPos = path[counter];
    orientation curOrientation = orientationMemory;
    bool isObstacle = robotExec.detect();
    bool isEnd = true;

    while(curPos != endPoint)
    {
        isObstacle = false;
        gExpiredTimer = false;
        if (nextPos == curPos + 1)
        {
            switch (curOrientation)
            {
                case NORTH:
                    turnRight();
                    break;
                
                case SOUTH:
                    turnLeft();
                    break;

                case EAST:
                    break;

                case WEST:
                    turn180();
                    break;
            }
            curOrientation = EAST;
            robotExec.startTimer(TIMER);
            while(!gExpiredTimer)
            {
                isObstacle = robotExec.detect();
            }
            robotExec.stopTimer();

            if(isObstacle)
            {
                isEnd = false;
                break;
            }
            driveLine();
        }
 

        else if (nextPos == curPos - 1)
        {
            switch (curOrientation)
            {
                case NORTH:
                    turnLeft();
                    break;
                
                case SOUTH:
                    turnRight();
                    break;

                case EAST:
                    turn180();
                    break;

                case WEST:
                    break;
            }
            curOrientation = WEST;

            robotExec.startTimer(TIMER);
            while(!gExpiredTimer)
            {
                isObstacle = robotExec.detect();
            }
            robotExec.stopTimer();

            if(isObstacle)
            {
                isEnd = false;
                break;
            }

            driveLine();
        }

        else if (nextPos == curPos + 7)
        {
            switch (curOrientation)
            {
                case NORTH:
                    turn180();
                    break;
                
                case SOUTH:
                    break;

                case EAST:
                    turnRight();
                    break;

                case WEST:
                    turnLeft();
                    break;
            }
            curOrientation = SOUTH;

            robotExec.startTimer(TIMER);
            while(!gExpiredTimer)
            {
                isObstacle = robotExec.detect();
            }
            robotExec.stopTimer();

            if(isObstacle)
            {
                isEnd = false;
                break;
            }

            driveLine();
        }

        else if (nextPos == curPos - 7)
        {
            switch (curOrientation)
            {
                case NORTH:
                    break;
                
                case SOUTH:
                    turn180();
                    break;

                case EAST:
                    turnLeft();
                    break;

                case WEST:
                    turnRight();
                    break;
            }
            curOrientation = NORTH;
            
            robotExec.startTimer(TIMER);
            while(!gExpiredTimer)
            {
                isObstacle = robotExec.detect();
            }
            robotExec.stopTimer();

            if(isObstacle)
            {
                isEnd = false;
                break;
            }

            driveLine();
        }
        curPos = nextPos;
        nextPos = path[counter++];
    }
    orientationMemory = curOrientation;
    if(isEnd)
    {
        robotExec.playSoundEnd();
    }
    else
    {
        robotExec.playSoundObstacle();
        robotExec.removePoint(nextPos);
        curPos = doTravelPoint(endPoint, curPos);
    }
    return curPos;
}

uint8_t doTravel(uint8_t x, uint8_t y, uint8_t startPoint = 0)
{
    uint8_t point = calculPoint(x,y);
    return doTravelPoint(point, startPoint);
}

#endif