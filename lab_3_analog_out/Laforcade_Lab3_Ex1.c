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


int main(int argc, char **argv)
{
    if(argc!=4){
        printf("Please choose [1] : Red, [2] : Green, [3] : Blue, between 0 and 255\n");
        return 2;
    }

    int LedPin[3] = {RED_PIN, GREEN_PIN, BLUE_PIN};
    int R = (atoi(argv[1])*100)/255;
    int G = (atoi(argv[2])*100)/255;
    int B = (atoi(argv[3])*100)/255;

    wiringPiSetupGpio();

    // Setup three PINS for Soft PWM
    for(int i=0;i<3;i++)
    {
        softPwmCreate(LedPin[i], 0, RANGE);
    }

    // Writing the value for PWM
    softPwmWrite(LedPin[0], R);  // Value for Red Pin
    softPwmWrite(LedPin[1], G); // Value for Green Pin
    softPwmWrite(LedPin[2], B);  // Value for Blue Pin
    sleep(10);

    return 0;
}


