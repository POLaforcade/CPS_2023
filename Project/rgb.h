#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

#define RED_PIN     16
#define GREEN_PIN   20
#define BLUE_PIN    21

class RGB
{

public:
    // Constructor
    RGB()
    {
        softPwmCreate(RED_PIN, 0, 255);
        softPwmCreate(GREEN_PIN, 0, 255);
        softPwmCreate(BLUE_PIN, 0, 255);
    }

    void Color(int R, int G, int B)
    {
        R = (255 - R) * 100 / 255.;
        G = (255 - G) * 100 / 255.;
        B = (255 - B) * 100 / 255.;

        softPwmWrite(RED_PIN, R);
        delay(10);
        softPwmWrite(GREEN_PIN, G);
        delay(10);
        softPwmWrite(BLUE_PIN, B);
        delay(10);

    }
};