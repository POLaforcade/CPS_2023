#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include <iostream>
#include <wiringPi.h>

#define PWM0 18

class servomotor
{

public: 
    servomotor()
    {
        pinMode(PWM0, OUTPUT);
        pwmSetMode(PWM_MODE_MS);
        pwmSetRange(180);
        pwmSetClock(2133);
    }

    void set(int angle)
    {
        pwmWrite(PWM0, angle);
    }
};

#endif