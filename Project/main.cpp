#include <stdio.h>
#include <cstdlib>

#include "keyboard.hpp"
#include "bgr.hpp"
#include "servomotor.hpp"

#define PIN_BUTTON 4

int code = 1111;
int admin = 1111;
bool locked = true;
bool is_opened = false;


void clear() {
    system("clear");
}

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
        // Decides if we should open/close the chest or not
        if(locked == false && is_opened == false)
        {
            // Opens the chest
            std::cout << "Opening the chest" << std::endl;
            setAngle(180);
            is_opened = true;
        }
        else
        {
            // Closes the chest
            std::cout << "Closing the chest" << std::endl;
            setAngle(0);
            is_opened = false;
        }
        delay(100);
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
    led_1.Color(255, 0, 0);

    // Control 
    Mode mode = ADMIN;
    char c;
    while(1)
    {
        c = getKey();
        delay(300);
        switch(mode)
        {
            case LOCKED:
                locked = true;
                if(c == 'A'){
                    std::cout << "Password : " << std::endl;
                    if(code == read_code())
                    {
                        std::cout << "Code is correct. Access granted..." << std::endl;
                        std::cout << "Welcome in mode UNLOCKED\n[A] To lock the chest" << std::endl;
                        led_1.Color(0, 255, 0);
                        mode = UNLOCKED;
                    }
                    else {
                        std::cout << "Wrong Code" << std::endl;
                    }
                }
                if(c == 'B'){
                    std::cout << "Password : " << std::endl;
                    if(read_code() == admin){
                        std::cout << "Welcome in mode ADMIN" << std::endl << "[A] To lock the chest\n[B] to change admin code\n[C] to change user code" << std::endl;
                        led_1.Color(255, 0, 0);
                        mode = ADMIN;
                    }
                }
                break;

            case UNLOCKED:
                locked = false;
                if(c == 'A')
                {
                    clear();
                    std::cout << "Locked chest\n[A] to unlock\n[B] to admin" << std::endl;
                    led_1.Color(0, 0, 255);
                    mode = LOCKED;
                }
                break;

            case ADMIN:
                locked = false;
                if(c=='A')
                {
                    clear();
                    std::cout << "Locked chest\n[A] to unlock\n[B] to admin" << std::endl;
                    led_1.Color(0, 0, 255);
                    mode = LOCKED;
                }
                if(c=='B')
                {
                    std::cout << "New admin code : " << std::endl;
                    admin = read_code();
                    std:: cout << std::setw(4) << std::setfill('0') << "Code entred = " << admin << std::endl;
                }
                if(c == 'C')
                {
                    std::cout << "New code : " << std::endl;
                    code = read_code();
                    std:: cout << std::setw(4) << std::setfill('0') << "Code entred = " << code << std::endl;
                }
                break;

            default:
                mode = ADMIN;
                break;
        }
    }

    return 0;
}