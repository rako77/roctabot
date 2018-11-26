#include "SpiderLeg.h"

SpiderLeg::SpiderLeg(Adafruit_PWMServoDriver *board, uint8_t forearmServoSlot, uint8_t bicepServoSlot, uint8_t shoulderServoSlot)
{
    forearm = SpiderServo(board, forearmServoSlot);
    bicep = SpiderServo(board, bicepServoSlot);
    shoulder = SpiderServo(board, shoulderServoSlot);
}

void SpiderLeg::SetAngles(uint8_t forearmAngle, uint8_t bicepAngle, uint8_t shoulderAngle)
{
    forearm.SetAngle(forearmAngle);
    shoulder.SetAngle(bicepAngle);
    bicep.SetAngle(shoulderAngle);
}

void SpiderLeg::SetAnglesSlow(uint8_t forearmAngle, uint8_t bicepAngle, uint8_t shoulderAngle, int degreesPerSecond)
{
    forearm.SetAngleSlow(forearmAngle, degreesPerSecond);
    shoulder.SetAngleSlow(bicepAngle, degreesPerSecond);
    bicep.SetAngleSlow(shoulderAngle, degreesPerSecond);
}

void SpiderLeg::Update()
{
    forearm.Update();
    shoulder.Update();
    bicep.Update();
}

bool SpiderLeg::Moving()
{
    return shoulder.Moving() || forearm.Moving() || bicep.Moving();
}