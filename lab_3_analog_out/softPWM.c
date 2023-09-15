#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

#define GPIO1 4
#define GPIO2 17
#define PWM_RANGE 100

int main(int argc, char *argv[])
{
   if (wiringPiSetupGpio() < 0) return 1;
       
    pinMode(GPIO1, OUTPUT);
    digitalWrite(GPIO1, LOW);
    //int softPwmCreate (int pin, int initialValue, int pwmRange) ;
    softPwmCreate(GPIO1, 0, PWM_RANGE);
    // void softPwmWrite (int pin, int value) ;
    softPwmWrite(GPIO1, 5);
    
    pinMode(GPIO2, OUTPUT);
    digitalWrite(GPIO2, LOW);
    softPwmCreate(GPIO2, 0, PWM_RANGE);
    softPwmWrite(GPIO2, 95);
    
    sleep(10); // You need to keep your program running to maintain the PWM output
}
