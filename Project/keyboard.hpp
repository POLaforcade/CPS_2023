#include <wiringPi.h>
#include <iostream>

const int ROW[] = {22, 10, 9, 11};
const int COLUMN[] = {12, 16, 20, 21};

class keyboard
{
public:
    keyboard(){}

    char getKey()
    {
        int i;
        int tmpRead;
        int rowVal = -1;
        int colVal = -1;
        char keyVal;

        for(i = 0; i < 4; i++){
            pinMode(COLUMN[i], OUTPUT);
            digitalWrite(COLUMN[i], LOW);
        }

        for(i = 0; i < 4; i++){
            pinMode(ROW[i], INPUT);
            pullUpDnControl(ROW[i], PUD_UP);
        }

        for(i = 0; i < 4; i++){
            tmpRead = digitalRead(ROW[i]);
            if(tmpRead == 0){
                rowVal = i;
            }
        }
        if(rowVal < 0 || rowVal > 3){
            return -1;
        }
        
        for(i = 0; i < 4; i++){
            pinMode(COLUMN[i], INPUT);
            pullUpDnControl(COLUMN[i], PUD_UP);
        }
        pinMode(ROW[rowVal], OUTPUT);
        digitalWrite(ROW[rowVal], LOW);
        for(i = 0; i < 4; i++){
            tmpRead = digitalRead(COLUMN[i]);
            if(tmpRead == 0){
                colVal = i;
            }
        }
        if(colVal < 0 || colVal > 3){
            return -1;
        }
        switch(rowVal){
            case 0:
            switch(colVal){
                case 0: keyVal = 1; break;
                case 1: keyVal = 2; break;
                case 2: keyVal = 3; break;
                case 3: keyVal = 'A'; break;
                default:
                break;
            }
            break;
            case 1:
            switch(colVal){
                case 0: keyVal = 4; break;
                case 1: keyVal = 5; break;
                case 2: keyVal = 6; break;
                case 3: keyVal = 'B'; break;
                default:
                break;
            }
            break;
            case 2:
            switch(colVal){
                case 0: keyVal = 7; break;
                case 1: keyVal = 8; break;
                case 2: keyVal = 9; break;
                case 3: keyVal = 'C'; break;
                default:
                break;
            }
            break;
            case 3:
            switch(colVal){
                case 0: keyVal = '*'; break;
                case 1: keyVal = 0; break;
                case 2: keyVal = '#'; break;
                case 3: keyVal = 'D'; break;
                default:
                break;
            }
            break;
            default:
            break;
        }
        return keyVal;
    }
};

typedef enum {
    S0,
    1KEY,
    2KEY,
    3KEY,
    4KEY,
    INCORRECT
} State;

int read_code()
{
    int key = -1;
    State current_state = S0

    std::cout<<"Rentrez votre code svp"<<std::endl;

    while(1)
    {
        int code = 0;
        key = keyboard_1.getKey();
        if(key != -1)
        {
            switch(current_state){
                case S0:
                    if(key >= 0 && key<=9)
                    {
                        code += key*1000;
                        current_state = 1KEY;
                    }
                    else{
                        current_state = INCORRECT;
                    }
                    break;
                case 1KEY:
                    if(key >= 0 && key<=9)
                    {
                        code += key*100;
                        current_state = 2KEY;
                    }
                    else{
                        current_state = INCORRECT;
                    }
                    break;
                case 2KEY:
                    if(key >= 0 && key<=9)
                    {
                        code += key;
                        current_state = 3KEY;
                    }
                    else{
                        current_state = INCORRECT;
                    }
                    break;
                case 3KEY:
                    if(key >= 0 && key<=9)
                    {
                        code += key;
                        current_state = 4KEY;
                    }
                    else{
                        current_state = INCORRECT;
                    }
                    break;
                case 4KEY:
                    return code;
                    break;
                case INCORRECT:
                    return -1;
                    break;
                case default:
                    break;
            }
        }
    }

    switch 
}