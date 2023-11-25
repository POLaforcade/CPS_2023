#include <stdio.h>
#include "keyboard.hpp"
#include "bgr.hpp"
#include "servomotor.hpp"

int main(void)
    {
    // Setup the depending on hardware
    if(wiringPiSetup() == -1) printf("setup wiringPi failed !\n");

    // Creating all the objects
    BGR led_1;
    keyboard keyboard_1;
    servomotor servo_1;

    // Control 
    int key = keyboard_1.getKey();
    printf("key rentre = %d\n", key);

    return 0;
}