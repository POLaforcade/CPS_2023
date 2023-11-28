#include <stdio.h>
#include "keyboard.hpp"
#include "bgr.hpp"
#include "servomotor.hpp"

int code = 0000;
int admin = 0000;
bool locked = true;

int main(void)
    {
    if(wiringPiSetupGpio() == -1) 
        printf("setup wiringPi failed !\n");

    // Creating all the objects
    BGR led_1;
    servomotor_setup();

    // Control
    while(1){
        code = read_code();
        printf("code rentre = %04d\n", code);
        delay(200);
    }

    return 0;
}