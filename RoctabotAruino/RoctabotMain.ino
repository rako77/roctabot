 
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "SpiderServo.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


SpiderServo forarm = SpiderServo(&pwm, 1);
SpiderServo Shoulder = SpiderServo(&pwm, 2);
SpiderServo bicep = SpiderServo(&pwm, 0);

void setup() 
{
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  forarm.SetAngle(90);
  Shoulder.SetAngle(90);
  bicep.SetAngle(90);
}


//forearm + is up 90 - 0
//bicep + is down 0 90
//shoulder + right 90
 int state = 0;
 #define TOTALSTATES 4
 int fstate[TOTALSTATES] = {60, 60, 20, 20};
 int bstate[TOTALSTATES] = {45, 120, 120, 45};
 int sstate[TOTALSTATES] = {90, 90, 90, 90};
 
 

void loop() {
  forarm.Update();
  Shoulder.Update();
  bicep.Update();

  if(!Shoulder.Moving() && !forarm.Moving() && !bicep.Moving()){
    state++;
    state %=TOTALSTATES;
    Shoulder.SetAngleSlow(sstate[state], 120);
    bicep.SetAngleSlow(bstate[state], 120);
    forarm.SetAngleSlow(fstate[state], 60);
  }
}
