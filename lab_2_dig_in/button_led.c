#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PIN_LED 4
#define PIN_BUTTON 18

int cnt = 0;
int N = 1;

void myISR(void)
{
    delay(10);
    if (digitalRead(PIN_BUTTON) == 0)
        printf("Button Pressed detected using ISR\n");
        cnt++;
    
    // Decides if we should turn on/off the LED
    if(cnt == N)
        digitalWrite (PIN_LED, HIGH) ;
    else
        if(cnt == 2*N){
            digitalWrite(PIN_LED, LOW) ;
            cnt = 0 ;
        }

    delay(50);
}

int main(int argc, char **argv)
{
    // Checks the number of args in command line
    if(argc!=2){
      printf("Please choose [1] : Number of press to change LED value\n");
      return 2;
    }

    N = atoi(argv[1]);

    // Setting up GPIO with wiringPi
    if(wiringPiSetupGpio() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !\n");
        return -1;
    }
    
    // Setting up GPIO pins
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    pullUpDnControl(PIN_BUTTON, PUD_DOWN);

    printf("Button pin has been setup.\n");
    
    if(wiringPiISR(PIN_BUTTON, INT_EDGE_FALLING, myISR) < 0){
        printf("ISR setup error!\n");
        return -1;
    }

    while(1){
        // Infinite loop
    }

    return 0;
}
