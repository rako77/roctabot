#ifndef SpiderLeg_h
#define SpiderLeg_h

#include "SpiderServo.h"

class SpiderLeg {
    private:
    SpiderServo forearm;
    SpiderServo bicep;
    SpiderServo shoulder;
    public:
    SpiderLeg();
    void Initialize(Adafruit_PWMServoDriver *board, uint8_t forearmServoSlot, uint8_t bicepServoSlot, uint8_t shoulderServoSlot);
    void SetAngles(uint8_t forearmAngle, uint8_t bicepAngle, uint8_t shoulderAngle);
    void SetAnglesSlow(uint8_t forearmAngle, uint8_t bicepAngle, uint8_t shoulderAngle, int degreesPerSecond);
    void Update();
    bool Moving();
};

#endif