#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "SpiderLeg.h"

#define LEG_NUM 4

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

SpiderLeg legs[LEG_NUM];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  uint8_t slot = 15;
  for (int i = 0; i < LEG_NUM; ++i) {
    legs[i].Initialize(&pwm, slot, slot-1, slot-2);
    legs[i].SetAngles(90,90,90);
    slot-=3;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < LEG_NUM; ++i) {
    legs[i].Update();
  }

  if (Serial.available() >= 5) {
    // read the incoming byte:
    uint8_t legNumber = Serial.read();
    uint8_t forearmAngle = Serial.read();
    uint8_t bicepAngle = Serial.read();
    uint8_t shoulderAngle = Serial.read();
    uint8_t degreesPerSecond = Serial.read();
    legs[legNumber%LEG_NUM].SetAnglesSlow(forearmAngle, bicepAngle, shoulderAngle, degreesPerSecond);    
  }
}