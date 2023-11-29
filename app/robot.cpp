#include "robot.h"

void robot::driveRatio(uint8_t leftRatio, uint8_t rightRatio, bool leftIsDrive, bool rightIsDrive)
{
    wheelsExec.driveRatio(leftRatio, rightRatio, leftIsDrive, rightIsDrive);
    return;
}

void robot::setGreen()
{
    ledExec.setGreen();
    return;
}

void robot::setRed()
{
    ledExec.setRed();
    return;
}

void robot::setAmber()
{
    ledExec.setAmber();
    return;
}

void robot::setDark()
{
    ledExec.setDark();
    return;
}

void robot::playNote(uint16_t note)
{
    soundExec.playNote(note);
    return;
}

void robot::stopSound()
{
    soundExec.stopSound();
    return;
}

uint8_t robot::readSensor()
{
    return lineFollowerExex.readSensors();
}

bool robot::detect()
{
    return obstacleDetectorExec.detect();
}

void robot::startTimer(uint16_t time)
{
    timerExec.startTimer(time);
    return;
}

void robot::stopTimer()
{
    timerExec.stopTimer();
    return;
}

void robot::playSoundEnd()
{
    for (uint8_t i = 0; i < 5; i++)
    {
        soundExec.playNote(4);
        _delay_ms(200);
        soundExec.stopSound();
        _delay_ms(100);
    }
    return;
}

void robot::playSoundObstacle()
{
    soundExec.playNote(20);
    _delay_ms(2000);
    soundExec.stopSound();
    return;
}

void robot::removePoint(uint8_t point)
{
    mapExec.removePoint(point);
}

void robot::resetMap() 
{
    map newMapExec; 
    mapExec = newMapExec;
}