#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include <iostream>
#include <wiringPi.h>

#define SERVO_PIN 18

const int SERVO_MIN_PWM = 100;
const int SERVO_MAX_PWM = 200;

int map(int alpha, int alpha_min, int alpha_max, int pulse_min, int pulse_max) {
    return (((pulse_max-pulse_min)*(alpha-alpha_min))/(alpha_max-alpha_min))+pulse_min;
}

void servomotor_setup() {
    pinMode(SERVO_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(192);
    pwmSetRange(2000);
}

void setAngle(int angle) {
    if (angle < 0) {
        angle = 0;
    } else if (angle > 180) {
        angle = 180;
    }
    int pwmValue = map(angle, 0, 180, SERVO_MIN_PWM, SERVO_MAX_PWM);
    pwmWrite(SERVO_PIN, pwmValue);
}

#endif