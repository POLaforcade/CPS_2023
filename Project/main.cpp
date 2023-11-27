#include <stdio.h>

#include "keyboard.hpp"
#include "bgr.hpp"
#include "servomotor.hpp"

int code = 0000;
int admin = 0000;
bool locked = true;
bool is_opened = false;

BGR led_1;
keyboard keyboard_1;
servomotor servo_1;


typedef enum
{
    LOCKED,
    UNLOCKED,
    ADMIN
} Mode;

void ISR_button(void)
{
    delay(10);
    // Make sure the button is pressed 1 time 
    if (digitalRead(PIN_BUTTON) == 0){
        printf("Button Pressed detected using ISR\n");
        // Decides if we should open/close the chest or not
        if(locked == false && super_locked == false && is_open == false)
        {
            // Opens the chest
            servo_1.setAngle(180);
            is_opened = true;
        }
        else
        {
            // Closes the chest
            servo_1.setAngle(0);
            is_opened = close;
        }
        delay(50);
    }
}

int main(void)
{
    // Setting up GPIO with wiringPi
    if(wiringPiSetupGpio() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !\n");
        return -1;
    }

    // Closes the chest by default
    servo_1.setAngle(0);

    // setup ISR for button 
    pinMode(PIN_BUTTON, INPUT);
    pullUpDnControl(PIN_BUTTON, PUD_DOWN);

    printf("Button pin has been setup.\n");
    
    if(wiringPiISR(PIN_BUTTON, INT_EDGE_FALLING, ISR_button) < 0){
        printf("ISR setup error!\n");
        return -1;
    }


    // Control 
    Mode mode = ADMIN;
    char c;
    while(1)
    {
        switch(Mode)
        {
            case LOCKED:
                locked = true
                c = keyboard_1.getKey();
                if(c == 'A')
                    int input = read_code(keyboard_1);
                    if(input == code)
                        mode = UNLOCKED;
                if(c == 'B')
                    int input = read_code(keyboard_1);
                    if(input == code)
                        mode = ADMIN;
                break;

            case UNLOCKED:
                locked = false
                c = keyboard_1.getKey();
                if(c == 'A')
                    mode = LOCKED;
                break;

            case ADMIN:
                c = keyboard_1.getKey();
                if(c=='A')
                    mode = LOCKED;
                else if(c == 'B')
                    admin = read_code(keyboard_1);
                else if(c == 'C')
                    code = read_code(keyboard_1);
                break;

            default:
                mode = ADMIN;
                break;
        }
    }

    return 0;
}