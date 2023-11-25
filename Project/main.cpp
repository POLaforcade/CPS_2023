#include <stdio.h>
#include "rgb.h"

int main()
{
    wiringPiSetupGpio();
    RGB LED_1;
    LED_1.Color(255, 255, 255);
    return 0;
}