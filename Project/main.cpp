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
        std::cout << "Button Pressed detected using ISR" << std::endl;
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
    // Setting up GPIO with wiringPi
    if(wiringPiSetupGpio() == -1){ //when initialize wiring failed,print message to screen
        std::cout << "setup wiringPi failed !" << std::endl;
        return -1;
    }

    BGR led_1;
    servomotor_setup();

    // Closes the chest by default
    setAngle(0);

    // setup ISR for button 
    pinMode(PIN_BUTTON, INPUT);
    pullUpDnControl(PIN_BUTTON, PUD_DOWN);
    
    if(wiringPiISR(PIN_BUTTON, INT_EDGE_FALLING, ISR_button) < 0){
        std::cout << "ISR setup error!" << std::endl;
        return -1;
    }
    std::cout << "Welcome in mode ADMIN" << std::endl << "[A] To lock the chest\n[B] to change admin code\n[C] to change user code" << std::endl;

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
                if(c == 'A'){
                    std::cout << "Password : ";
                    if(code == read_code()){
                        std::cout << "Code is correct. Access granted..." << std::endl;
                        delay(1000);
                        std::cout << "Welcome in mode UNLOCKED\n[A] To lock the chest lock" << std::endl;
                        mode = UNLOCKED;
                    }
                    else {
                        std::cout << "Wrong Code" << std::endl;
                    }
                }
                else if(c == 'B'){
                    std::cout << "Password : ";
                    if(read_code() == admin){
                        std::cout << "Welcome in mode ADMIN" << std::endl << "[A] To lock the chest\n[B] to change admin code\n[C] to change user code" << std::endl;
                        mode = ADMIN;
                    }
                }
                break;

            case UNLOCKED:
                locked = false;
                c = getKey();
                if(c == 'A')
                    std::cout << "Locked chest\n[A] to unlock\n[B] to admin" << std::endl;
                    mode = LOCKED;
                break;

            case ADMIN:
                c = getKey();
                if(c=='A')
                {
                    std::cout << "Locked chest\n[A] to unlock\n[B] to admin" << std::endl;
                    mode = LOCKED;
                }
                if(c=='B')
                {
                    std::cout << "New admin code : " << std::endl;
                    admin = read_code();
                    std:: cout << "code rentre = " << code << std::endl;
                    std::cout << "Admin Code changed" << std::endl;
                }
                if(c == 'C')
                {
                    std::cout << "New code : " << std::endl;
                    code = read_code();
                    std:: cout << "code rentre = " << code << std::endl;
                    std::cout << "Code changed" << std::endl;
                }
                break;

            default:
                mode = ADMIN;
                break;
        }
        delay(200);
    }

    return 0;
}