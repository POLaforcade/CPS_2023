#include <stdio.h>
#include <unistd.h>
#include <wiringPiI2C.h>

#define X_REG 0x32
#define Y_REG 0x34
#define Z_REG 0x36
#define DEV_ADDRESS 0x53

short int axis_sample_average(int axis, int fd)
{
	int c = 100;
	int value = 0;

	while(c--){
		value += axis_sample(axis, fd);
	}

	return ( value/100 );
}

int main(int argc, char* argv[])
{
    int fd = 0;
	short int data = 0;	
	short int data2 = 0;
	int datasimple = 0;	

	fd = wiringPiI2CSetup(DEV_ADDRESS);

	// Data Format Register
	datasimple = wiringPiI2CReadReg8(fd,0x31);
	wiringPiI2CWriteReg8(fd,0x31,datasimple|0xb);

	wiringPiI2CWriteReg8(fd,0x2d,0x08); //POWER_CTL	
	usleep(11000);

    // erase offset bits
	wiringPiI2CWriteReg8(fd,0x1e,0);
	wiringPiI2CWriteReg8(fd,0x1f,0);
	wiringPiI2CWriteReg8(fd,0x20,0);
	usleep(11000);
	// calibrate X axis
	data = axis_sample_average(X_REG,fd);
	wiringPiI2CWriteReg8(fd,0x1e,-(data / 4));
	// calibrate Y axis
	data = axis_sample_average(Y_REG,fd);
	wiringPiI2CWriteReg8(fd,0x1f,-(data / 4));
	// calibrate Z axis
	data = axis_sample_average(Z_REG,fd);
	wiringPiI2CWriteReg8(fd,0x20,-((data - 256 ) / 4));

	return 0;
}