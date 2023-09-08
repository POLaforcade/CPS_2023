#include <wiringPi.h>
#include <stdio.h>

#define PIN_BUTTON 18

void myISR(void)
{
    printf("Button Pressed detected using ISR\n");
    delay(50);
}

int main(void)
{
    if(wiringPiSetupGpio() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !\n");
        return -1;
    }
    
    pinMode(PIN_BUTTON, INPUT);
    pullUpDnControl(PIN_BUTTON, PUD_UP);
    
    if(wiringPiISR(PIN_BUTTON, INT_EDGE_FALLING, myISR) < 0){
        printf("ISR setup error!\n");
        return -1;
    }

    while(1){
        // Infinite loop
    }

    return 0;
}

