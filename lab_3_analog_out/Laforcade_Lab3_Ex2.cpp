#include <iostream>
#include <wiringPi.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<stdio.h>

using namespace std;

#define PWM0 12
#define PIN_BUTTON 18

int cnt = 0;
int N;

void myISR(void)
{
   delay(10);

   if (digitalRead(PIN_BUTTON) == 0){
      cnt += 1;
      if(cnt>N)
         cnt = 0;
      pwmWrite(PWM0, (128/N)*cnt);
   }

   delay(50);
}

int main(int argc, char **argv){

   if(argc!=2){
       printf("Please choose [1] : N, the steps to full brightness\n");
       return 2;
   }

   N = atoi(argv[1]);
   
   wiringPiSetupPhys();
   pinMode(PWM0, PWM_OUTPUT);
   pinMode(PIN_BUTTON, INPUT);
   pullUpDnControl(PIN_BUTTON, PUD_DOWN);

   cout << "Button pin has been setup." << endl;

   pwmSetMode(PWM_MODE_MS);
   pwmSetRange(128);
   pwmSetClock(15);

   cout << "The PWM Output is enabled" << endl;

   if(wiringPiISR(PIN_BUTTON, INT_EDGE_FALLING, myISR) < 0){
      printf("ISR setup error!\n");
      return -1;
   }

   while(1){
      // Loop 
   }
}