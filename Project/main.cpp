#include "bgr.hpp"
#include "servomotor.hpp"

int main()
{
    wiringPiSetupGpio();
    servomotor servo_1;
    servo_1.set(90)
}