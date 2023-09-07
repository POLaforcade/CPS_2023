#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(char filename[], char value[])
{
   FILE* fp;                           // create a file pointer fp
   fp = fopen(filename, "w");          // open file for writing
   fprintf(fp, "%s", value);           // send the value to the file
   fclose(fp);                         // close the file using fp
}

int main(int argc, char* argv[]){
   if(argc!=3){                       // We should have 3 args to run the program : program_name GPIO_pin nb_blink
      printf("Please choose [1] : GPIO Pin, [2] : number of time LED should blink\n");
      return 2;
   }

   char* GPIO_FILE = "/sys/class/gpio/gpio";

   int nb_gpio = atoi(argv[1]);
   int nb_blink = atoi(argv[2]);
   printf("Starting the blink LED program %d times on GPIO %d\n", nb_blink, nb_gpio);

   // Setup the path to the correct GPIO
   strcat(GPIO_FILE, argv[1]);
   strcat(GPIO_FILE, "/");
   printf("%s\n", GPIO_FILE);

   // // setup GPIO pin
   // printf("Setting up the LED on the GPIO\n");
   // writeGPIO(GPIO_SYSFS "export", str_gpio);
   // usleep(100000);
   // writeGPIO(GPIO_FILE "direction", "out");
   // // blink
   // for(int i=0; i<nb_blink; i++)
   // {
   //    writeGPIO(GPIO_FILE "value", "1");
   //    usleep(500000);
   //    writeGPIO(GPIO_FILE "value", "0");
   //    usleep(500000);
   // }
   // // unexport GPIO pin
   // writeGPIO(GPIO_SYSFS "unexport", str_gpio);
   return 0;
}