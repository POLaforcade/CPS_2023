#include "bgr.hpp"
#include "servomotor.hpp"

int main()
{
    wiringPiSetupGpio();
    BGR led1;
    led1.Color(0, 0, 0);
    return 0;
}