#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

#define PIN_BUTTON 18

int main (int argc, char **argv)
{
    wiringPiSetupGpio();

    pinMode(PIN_BUTTON, INPUT);
    pullUpDnControl(PIN_BUTTON, PUD_UP);

    printf("Button pin has been setup.\n");
    
    while (1)
    {
        if (digitalRead(PIN_BUTTON) == 0) {
            printf("Button pressed\n");
        }
        delay(100);
    }
}
