#include "SpiderServo.h"

#include <Arduino.h>

#define MIN_PULSE_WIDTH 500
#define MAX_PULSE_WIDTH 2500
#define DEFAULT_PULSE_WIDTH 1500

SpiderServo::SpiderServo(Adafruit_PWMServoDriver *board, uint8_t servoSlot)
{
    this->board = board;
    this->_servoSlot = servoSlot;
}

int SpiderServo::pulseWidth(int angle)
{
    int pulse_wide, analog_value;
    pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
    analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
    return analog_value;
}

void SpiderServo::SetAngle(int angle)
{
    targetPulseWidth = pulseWidth(angle);
    board->setPWM(_servoSlot, 0, targetPulseWidth);
    previousPulseWidth = targetPulseWidth;
}

void SpiderServo::SetAngleSlow(int angle, int degreesPerSecond)
{
    targetPulseWidth = pulseWidth(angle);
    operationStartTime = millis();
    double pulseWidthPerMs;
    pulseWidthPerS = degreesPerSecond * (double)(pulseWidth(180)-pulseWidth(0)) / 180;
}

void SpiderServo::Update()
{
    if (targetPulseWidth != previousPulseWidth)
    {
        int newPulseWidth;
        int pulseWidthChange = int((millis() - operationStartTime)*pulseWidthPerS/1000);
        if (targetPulseWidth > previousPulseWidth)
        {
            newPulseWidth = previousPulseWidth + pulseWidthChange;
            if (newPulseWidth >= targetPulseWidth)
            {
                newPulseWidth = targetPulseWidth;
                previousPulseWidth = targetPulseWidth;
            }
        }
        else{
            newPulseWidth = previousPulseWidth - pulseWidthChange;
            if (newPulseWidth <= targetPulseWidth)
            {
                newPulseWidth = targetPulseWidth;
                previousPulseWidth = targetPulseWidth;
            }
        }
        
        
        board->setPWM(_servoSlot, 0, newPulseWidth);
    }
}

bool SpiderServo::Moving()
{
    return (targetPulseWidth != previousPulseWidth);
}
