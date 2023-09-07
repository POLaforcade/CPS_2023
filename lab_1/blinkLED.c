#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_SYSFS "/sys/class/gpio/"
#define GPIO_FILE "/sys/class/gpio/gpio"

void writeGPIO(char filename[], char value[])
{
   FILE* fp;                           // create a file pointer fp
   fp = fopen(filename, "w");         // open file for writing
   fprintf(fp, "%s", value);           // send the value to the file
   fclose(fp);                         // close the file using fp
}

int main(int argc, char* argv[]){

   printf("Recuperation des parametres");

   int nb_gpio;
   int nb_blink;

   if(argc!=3)// We should have 3 args to run the program : program_name GPIO_pin nb_blink
   { 
      printf("Please choose [1] : GPIO Pin, [2] : number of time LED should blink");
      return 2;
   }

   // sscanf(argv[2], "%d", &nb_gpio);
   // sscanf(argv[3], "%d", &nb_blink);

   // printf("Starting the blink LED program %d times on GPIO %s\n", nb_blink, argv[2]);

   // // Setup the path to the correct GPIO
   // strcat(GPIO_FILE, argv[2]);
   // strcat(GPIO_FILE, "/");

   // // setup GPIO pin
   // printf("Setting up the LED on the GPIO\n");
   // writeGPIO(GPIO_SYSFS "export", argv[2]);
   // usleep(100000);
   // writeGPIO(GPIO_FILE "direction", "out");

   // // blink
   // for(int i=0; i<nb_blink; i++)
   // {
   //    writeGPIO(GPIO_FILE "value", "1");
   //    usleep(1000000);
   //    writeGPIO(GPIO_FILE "value", "0");
   //    usleep(1000000);
   // }

   // // unexport GPIO pin
   // writeGPIO(GPIO_SYSFS "unexport", argv[2]);
}