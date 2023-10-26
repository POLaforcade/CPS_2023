#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define MotorPin_A          4
#define MotorPin_B          5



// the setup function runs once when you press reset or power the board
void setup(void) {
  // initialize pins as an output.
  pinMode(MotorPin_A, OUTPUT);
  pinMode(MotorPin_B, OUTPUT);
}

// the loop function runs over and over again forever
void loop(void) {
  // Spin the motor clockwise direction for 2 seconds
  digitalWrite(MotorPin_A,HIGH);
  digitalWrite(MotorPin_B,LOW); // To change the speed, use PWM in this pin
  delay(2000);

  // Spin the motor in the opposite direction for 2 seconds
  digitalWrite(MotorPin_A,LOW);
  digitalWrite(MotorPin_B,HIGH); // To change speed, use PWM in this pin
  delay(2000);
}


void stop(void)
{
  digitalWrite(MotorPin_A,HIGH);
  digitalWrite(MotorPin_B,HIGH);
}

int main(void)
{
    if(wiringPiSetup() == -1){
        printf("setup wiringPi failed !\n");
        return -1; 
    }

    setup();

    loop();

    stop();
}

