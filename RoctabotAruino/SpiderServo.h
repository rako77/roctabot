#include <Adafruit_PWMServoDriver.h>

#define FREQUENCY 50

class SpiderServo {
    private:
    Adafruit_PWMServoDriver *board;
    uint8_t _servoSlot;
    int targetPulseWidth;
    int previousPulseWidth;
    unsigned long operationStartTime;
    double pulseWidthPerS;

    public:
    SpiderServo(Adafruit_PWMServoDriver *board, uint8_t servoSlot);
    void SetAngle(int angle);
    void SetAngleSlow(int angle, int degreesPerSecond);
    void Update();
    bool Moving();

    private:
    int pulseWidth(int angle);
};
