#include <stdio.h>
#include <stdlib.h>

#define   LOWER  0       /* lower limit of table */
#define   UPPER  300     /* upper limit */
#define   STEP   20      /* step size */

/* print Fahrenheit-Celsius table */
int convert(int n) {
  printf("Fahrenheit: %3d, Celcius: %6.1f\n", n, (5.0/9.0)*(n-32));
}

int convertRange(int start, int end, int increment) {
  int n = start;
  while (n <= end) {
    printf("Fahrenheit: %3d, Celcius: %6.1f\n", n, (5.0/9.0)*(n-32));
    n = n + increment;
  }
}

int main(int argc, char **argv) {
  int fahr, start, end, increment;
  if (argc < 2) {
    printf("You need to send the number of grades to convert\n");
    printf("How to execute option one: ./fc <number>\n");
    return 1;
  }
  else if (argc == 2) {
    fahr = atoi(argv[1]); //atoi converts a string into a integer
    convert(fahr);
    return 0;
  }
  else if (argc < 4) {
    printf("How to execute option two: ./fc <start> <end> <increment>\n");
    return 1;
  }
  else if (argc == 4) {
    start = atoi(argv[1]);
    end = atoi(argv[2]);
    increment = atoi(argv[3]);
    convertRange(start, end, increment);
    return 0;
  }
}
