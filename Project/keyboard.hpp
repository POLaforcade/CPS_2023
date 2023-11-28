#include <wiringPi.h>
#include <iostream>
#include <stdio.h>

const int ROW[]    = {22, 10, 11, 9};
const int COLUMN[] = {12, 16, 20, 21};

// Reads a key from the keyboard
int getKey(void)
{
	int i;
	int tmpRead;
	int rowVal = -1;
	int colVal = -1;
	char keyVal = -1;

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

	//printf("%d, %d\n", rowVal, colVal);
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

typedef enum {
    S0,
    KEY1,
    KEY2,
    KEY3,
    KEY4,
    INCORRECT
} State;

int read_code()
{
    int tmp_key = -1;
    int res = 0;
    State current_state = S0;
    std::cout<<"Rentrez votre code svp"<<std::endl;
    while(1)
    {
        tmp_key = getKey();
        if(tmp_key != -1)
        {
            std::cout<<"key ="<<key << std::endl;
            switch(current_state){
                case S0:
                    if(tmp_key >= 0 && tmp_key<=9)
                    {
                        res += tmp_key*1000;
                        current_state = KEY1;
                        printf("*");
                    }
                    else{
                        current_state = INCORRECT;
                    }
                    break;
                case KEY1:
                    if(tmp_key >= 0 && tmp_key<=9)
                    {
                        res += tmp_key*100;
                        current_state = KEY2;
                        printf("*");
                    }
                    else{
                        current_state = INCORRECT;
                    }
                    break;
                case KEY2:
                    if(tmp_key >= 0 && tmp_key<=9)
                    {
                        res += 10*tmp_key;
                        current_state = KEY3;
                        printf("*");
                    }
                    else{
                        current_state = INCORRECT;
                    }
                    break;
                case KEY3:
                    if(tmp_key >= 0 && tmp_key<=9)
                    {
                        res += tmp_key;
                        current_state = KEY4;
                        printf("*");
                    }
                    else{
                        current_state = INCORRECT;
                    }
                    break;
                case KEY4:
                    if(tmp_key == '#'){
                        return res;
                    }
                    else
                        current_state = INCORRECT; 
                    break;
                case INCORRECT:
                    return -1;
                    break;
                default:
                    break;
            }
            delay(400);
        }
    }
}