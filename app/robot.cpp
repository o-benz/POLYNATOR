#include "robot.h"

void robot::driveRatio(uint8_t leftRatio, uint8_t rightRatio, bool leftIsDrive, bool rightIsDrive)
{
    wheelsExec.driveRatio(leftRatio, rightRatio, leftIsDrive, rightIsDrive);
}

void robot::setGreen()
{
    ledExec.setGreen();
}

void robot::setRed()
{
    ledExec.setRed();
}

void robot::setAmber()
{
    ledExec.setAmber();
}

void robot::setDark()
{
    ledExec.setDark();
}

void robot::playNote(uint16_t note)
{
    soundExec.playNote(note);
}

void robot::stopSound()
{
    soundExec.stopSound();
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
}

void robot::stopTimer()
{
    timerExec.stopTimer();
}