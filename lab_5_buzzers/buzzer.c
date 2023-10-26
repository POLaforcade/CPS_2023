/*
* File name   : buzzer.c
* Description : Make an active buzzer sound.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/05/02
*/
#include <wiringPi.h>
#include <stdio.h>

#define BeepPin 1

int main(void)
{
    
	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !");
		return -1; 
	}
	
	pinMode(BeepPin, OUTPUT);   //set GPIO0 output

    // Code for S8050
    digitalWrite(BeepPin, HIGH);  //beep on
    delay(1000);                 //delay
    digitalWrite(BeepPin, LOW);  //beep off
    delay(5);                    //delay


	return 0;
}

