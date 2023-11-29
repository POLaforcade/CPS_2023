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
    
    if(wiringPiISR(PIN_BUTTON, INT_EDGE_FALLING, ISR_button) < 0){
        printf("ISR setup error!\n");
        return -1;
    }
    std::cout << "Welcome in mode ADMIN" << std::endl << "[A] To lock the chest\n[B] to change admin code\n[C] to change user code" << std::endl;

    // Control 
    Mode mode = ADMIN;
    char c;
    while(1)
    {
        switch(mode)
        {
            case LOCKED:
                locked = true;
                delay(200);
                c = getKey();
                if(c == 'A'){
                    printf("password : ");
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
                    printf("Password : ");
                    delay(200);
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
                    std::cout << "New admin code : ";
                    //admin = read_code();
                    printf("cod e rentre = %04d\n", admin);
                    std::cout << "Admin Code changed" << std::endl;
                }
                if(c == 'C')
                {
                    printf("New code : ");
                    code = read_code();
                    printf("code rentre = %04d\n", code);
                    std::cout << "Code changed" << std::endl;
                }
                break;

            default:
                mode = ADMIN;
                break;
        }
    }

    return 0;
}