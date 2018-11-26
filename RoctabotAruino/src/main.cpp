#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "SpiderLeg.h"

#define LEG_NUM 4

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

SpiderLeg legs[LEG_NUM];

void setup() {
  // put your setup code here, to run once:
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  uint8_t slot = 0;
  for (int i = 0; i < LEG_NUM;++i){
    legs[i] = SpiderLeg(&pwm, slot, slot+1, slot+2);
    legs[i].SetAngles(90,90,90);
    slot+=3;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}