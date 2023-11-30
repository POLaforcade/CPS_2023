#include "servomotor.hpp"

int main()
{
    // Setting up GPIO with wiringPi
    if(wiringPiSetupGpio() == -1){ //when initialize wiring failed,print message to screen
        std::cout << "setup wiringPi failed !" << std::endl;
        return -1;
    }

    servomotor_setup();
    setAngle(180);
    return 0;
}