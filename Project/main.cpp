#include "rgb.h"

int main()
{
    wiringPiSetupGpio();
    RGB LED_1;
    LED_1.Color(255, 0, 0);
    return 0;
}