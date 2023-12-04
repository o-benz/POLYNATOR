#pragma once
#define BUTTON_DEBOUNCE_DELAY 50


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "button.h"
#include "led.h"
#include "sound.h"
#include "timer.h"
#include "wheels.h"
#include "lineFollower.h"
#include "obstacleDetector.h"
#include "map.h"

class robot;

class robot
{
public:
    robot(){};
    ~robot(){};
    void driveRatio(uint8_t leftRatio, uint8_t rightRatio, bool leftIsDrive = true, bool rightIsDrive = true);
    void setGreen();
    void setRed();
    void setAmber();
    void setDark(); 
    void playNote(uint16_t note);
    void stopSound();
    uint8_t readSensor();
    bool detect();
    void startTimer(uint16_t time);
    void stopTimer();
    void playSoundEnd();
    void playSoundObstacle();
    void removePoint(uint8_t point);
    map mapExec;
    void resetMap();
    
private:
    timer timerExec;
    obstacleDetector obstacleDetectorExec;
    lineFollower lineFollowerExex;
    wheels wheelsExec;
    sound soundExec;
    led ledExec;
    button buttonExec;
};