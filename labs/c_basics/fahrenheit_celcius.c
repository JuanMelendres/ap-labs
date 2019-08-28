#include <stdio.h>

#define   LOWER  0       /* lower limit of table */
#define   UPPER  300     /* upper limit */
#define   STEP   20      /* step size */

/* print Fahrenheit-Celsius table */

int main(int argc, char **argv)
{
    int fahr;
    if (argc < 2)
    {
      printf("You need to send the number of grades to convert\n");
      printf("How to execute: ./fc <number>\n");
      return 1;
    }
    fahr = atoi(argv[1]); //atoi converts a string into a integer

    printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));

    return 0;
}
