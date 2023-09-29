#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<stdio.h>

#define RANGE       100
#define RED_PIN     17
#define GREEN_PIN   27
#define BLUE_PIN    22

void extractRGBFromString(char *rgbString, int *red, int *green, int *blue) {
    *red = strtol(rgbString + 2, NULL, 16);
    *green = strtol(rgbString + 4, NULL, 16);
    *blue = strtol(rgbString + 6, NULL, 16);
}

int main(int argc, char **argv)
{
    if(argc!=2){
        printf("Please choose [1] : RGB values\n");
        return 2;
    }

    int LedPin[3] = {RED_PIN, GREEN_PIN, BLUE_PIN};
    int R, G, B;
    extractRGBFromString(argv[1], &R, &G, &B);
    printf("%d %d %d \n", R, G, B);
    R = 255-(R>>16);
    G = 255-(G>>8),
    B = 255-B;

    wiringPiSetupGpio();

    // Setup three PINS for Soft PWM
    for(int i=0;i<3;i++)
    {
        softPwmCreate(LedPin[i], 0, RANGE);
    }

    printf("%d %d %d \n", R, G, B);

    // Writing the value for PWM
    softPwmWrite(LedPin[0], R);  // Value for Red Pin
    softPwmWrite(LedPin[1], G); // Value for Green Pin
    softPwmWrite(LedPin[2], B);  // Value for Blue Pin

    return 0;
}


