#include <wiringPi.h>
#include <softPwm.h>

#define RANGE       100
#define RED_PIN     17
#define GREEN_PIN   27
#define BLUE_PIN    22


int main()
{
    int LedPin[3] = {RED_PIN, GREEN_PIN, BLUE_PIN};

    int i=0;

    // Check how to Setup - http://wiringpi.com/reference/setup/
    wiringPiSetupGpio();

    for(i=0;i<3;i++) // Setup three PINS for Soft PWM
    {
        //int softPwmCreate (int pin, int initialValue, int pwmRange) ;
        softPwmCreate(LedPin[i], 0, RANGE);
    }
    // void softPwmWrite (int pin, int value) ;
    // Note: If you have a Common Anode RGB LED, 
    // 0 indicates maximum intensity
    // If you have a Common Cathode RGB LED, 
    // 100 indicates maximum intensity.
    softPwmWrite(LedPin[0], 0);  // Value for Red Pin
    softPwmWrite(LedPin[1], 100); // Value for Green Pin
    softPwmWrite(LedPin[2], 0);  // Value for Blue Pin
    sleep(10); // You need to keep your program running to maintain the PWM output

    return 0;
}


