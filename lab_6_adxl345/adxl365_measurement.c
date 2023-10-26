#include <stdio.h>
#include <unistd.h>
#include <wiringPiI2C.h>

#define X_REG 0x32
#define Y_REG 0x34
#define Z_REG 0x36
#define DEV_ADDRESS 0x53

short int axis_sample(int axis,int fd)
{
	short int data = 0;
	short int data2 = 0;

	usleep(10000);
	data  =  wiringPiI2CReadReg8(fd,axis);
	data2 =  wiringPiI2CReadReg8(fd,axis+1); 
	
	return ( (data2<<8)|data );
}

int main(int argc, char* argv[])
{
	if(argc!=4){
      printf("Please choose [1] : number of g, [2] : number of second to sample, [3] : output file\n");
      return 2;
   }

	int fd = wiringPiI2CSetup(DEV_ADDRESS);
	short int data = 0;	
	short int data2 = 0;
	int datasimple = 0;	
	int time_in_s = atoi(argv[2]);

	// Data Format Register
	datasimple = wiringPiI2CReadReg8(fd,0x31);
	wiringPiI2CWriteReg8(fd,0x31,datasimple|0xb);

	wiringPiI2CWriteReg8(fd,0x2d,0x08); //POWER_CTL	
	usleep(11000);

	float gravity_range = atof(argv[1]); // plus/minus n g
	float resolution = 8192; // 13 bit resolution
	float factor = gravity_range/resolution;

	FILE *file = fopen(argv[3], "w");
    if (file == NULL) {
        printf("can't open the file.\n");
        return 1;
    }


	fprintf(file, "X, Y, Z\n");  // Header
    for (int i = 0; i < time_in_s * 10; i++) {
        float x = axis_sample(X_REG, fd) * gravity_range;
        float y = axis_sample(Y_REG, fd) * gravity_range;
        float z = axis_sample(Z_REG, fd) * gravity_range;

        fprintf(file, "%f, %f, %f\n", x, y, z);
        usleep(100000);  // Sleep for 100 milliseconds
    }
	return 0;
}