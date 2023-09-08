#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_SYSFS "/sys/class/gpio/"
#define GPIO_PATH  "/sys/class/gpio/gpio"

void writeGPIO(char filename[], char value[])
{
   FILE* fp;                           // create a file pointer fp
   fp = fopen(filename, "w");          // open file for writing
   if(fp == NULL){
      perror("Error while opening the file");
      exit(0);
   }
   printf("writing the value : %s, in the file : %s\n", value, filename);
   fprintf(fp, "%s", value);           // send the value to the file
   fclose(fp);                         // close the file using fp
}

int main(int argc, char* argv[]){
   if(argc!=3){                       // We should have 3 args to run the program : program_name GPIO_pin nb_blink
      printf("Please choose [1] : GPIO Pin, [2] : number of time LED should blink\n");
      return 2;
   }

   int nb_gpio = atoi(argv[1]);
   int nb_blink = atoi(argv[2]);
   printf("Starting the blink LED program %d times on GPIO %d\n", nb_blink, nb_gpio);

   // Setup the path to the correct GPIO
   char GPIO_FILE[100] = GPIO_PATH;
   strcat(GPIO_FILE, argv[1]);
   strcat(GPIO_FILE, "/");

   // setup GPIO pin
   char GPIO_EXP[100] = GPIO_SYSFS;
   strcat(GPIO_EXP, "export");

   writeGPIO(GPIO_EXP,argv[1]);
   usleep(100000);

   char GPIO_DIR[100] = GPIO_PATH;
   strcat(GPIO_DIR, "direction");
   writeGPIO(GPIO_DIR, "out");

   // blink
   char GPIO_VAL[100] = GPIO_PATH;
   strcat(GPIO_VAL, "value");
   printf("Setting up the LED on the GPIO\n");
   for(int i=0; i<nb_blink; i++)
   {
      writeGPIO(GPIO_VAL, "1");
      usleep(500000);
      writeGPIO(GPIO_VAL, "0");
      usleep(500000);
   }

   // unexport GPIO pin
   writeGPIO(GPIO_SYSFS "unexport", argv[1]);
   return 0;
}