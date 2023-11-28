#include <stdio.h>

#include "keyboard.hpp"
#include "bgr.hpp"
#include "servomotor.hpp"

#define PIN_BUTTON 4

int code = 0000;
int admin = 0000;
bool locked = true;
bool is_opened = false;

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
        if(locked == false && is_opened == false)
        {
            // Opens the chest
            setAngle(180);
            is_opened = true;
        }
        else
        {
            // Closes the chest
            setAngle(0);
            is_opened = false;
        }
        delay(50);
    }
}

int main(void)
{
    printf("test");
    // Setting up GPIO with wiringPi
    if(wiringPiSetupGpio() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !\n");
        return -1;
    }

    BGR led_1;
    servomotor_setup();

    // Closes the chest by default
    setAngle(0);

    // setup ISR for button 
    pinMode(PIN_BUTTON, INPUT);
    pullUpDnControl(PIN_BUTTON, PUD_DOWN);

    printf("Button pin has been setup.\n");
    
    if(wiringPiISR(PIN_BUTTON, INT_EDGE_FALLING, ISR_button) < 0){
        printf("ISR setup error!\n");
        return -1;
    }
    std::cout << "Welcome in mode ADMIN" << std::endl;

    // Control 
    Mode mode = ADMIN;
    char c;
    while(1)
    {
        c = -1;
        switch(mode)
        {
            case LOCKED:
                locked = true;
                c = getKey();
                if(c == 'A')
                {
                    if(read_code() == code)
                    {
                        std::cout << "Valid Code\nUnlocked chest, Press[A] for lock " << std::endl;
                        mode = UNLOCKED;
                    }
                }
                else if(c == 'B')
                {
                    if(read_code() == admin)
                        mode = ADMIN;
                }
                else if(c != -1)
                {
                    std::cout << c; // "Error, Press[A] for unlock and [B] for admin" << std::endl;
                }
                break;

            case UNLOCKED:
                locked = false;
                c = getKey();
                if(c == 'A')
                    mode = LOCKED;
                break;

            case ADMIN:
                c = getKey();
                if(c=='A')
                {
                    std::cout << "Locked chest, Press[A] for unlock and [B] for admin" << std::endl;
                    mode = LOCKED;
                    delay(200);
                }
                else if(c == 'B')
                {
                    std::cout << "Code changed" << std::endl;
                    admin = read_code();
                }
                else if(c == 'C')
                {
                    code = read_code();
                    std::cout << "Admin Code changed" << std::endl;
                }
                break;

            default:
                mode = ADMIN;
                break;
        }
    }

    return 0;
}