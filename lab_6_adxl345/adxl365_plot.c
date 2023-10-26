#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc!=4){
      printf("Please choose [1] : number of g, [2] : number of second to sample, [3] : output file\n");
      return 2;
   }

   int time_in_s = atoi(argv[2]);
   float gravity_range = atof(argv[1]);;
   char* filename = argv[3];

    printf("Data for the %s file, for %d secondes and %f precision in g\n\n");

    // Open CSV file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    double acceleration_x, acceleration_y, acceleration_z;
    while (fscanf(file, "%lf,%lf,%lf", &acceleration_x, &acceleration_y, &acceleration_z) == 3) {
        printf("X: %.2f , Y: %.2f , Z: %.2f \n", acceleration_x, acceleration_y, acceleration_z);
    }

    // Fermer le fichier après lecture
    fclose(file);

    return 0;
}