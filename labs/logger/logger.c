#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define RESET 0
#define BRIGHT 1
#define DIM	2
#define UNDERLINE 3
#define BLINK	4
#define REVERSE 7
#define HIDDEN 8

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define	WHITE 7

/*
  Using the colors references that the profesor give us in a link,
  I find textcolor function and #define that are made by Pradeep Padala.
*/
void textcolor(int attr, int fg, int bg) {
  char command[13];
	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

/*
  I find this information about Variable Argument Lists, that would help me to create the solution
  https://www.cprogramming.com/tutorial/c/lesson17.html
*/
int infof(const char *format, ...) {
  int flag;
  va_list arg;
  textcolor (BRIGHT, WHITE, HIDDEN);
  printf ("MESSAGE: ");
  textcolor (RESET, WHITE, HIDDEN);
  va_start (arg, format);
  flag = vprintf (format, arg);
  va_end (arg);
  return flag;
}

int warnf(const char *format, ...) {
  int flag;
  va_list arg;
  textcolor (BRIGHT, YELLOW, HIDDEN);
  printf ("MESSAGE: ");
  textcolor (RESET, YELLOW, HIDDEN);
  va_start (arg, format);
  flag = vprintf (format, arg);
  va_end (arg);
  return flag;
}

int errorf(const char *format, ...) {
  int flag;
  va_list arg;
  textcolor (BRIGHT, RED, HIDDEN);
  printf ("MESSAGE: ");
  textcolor (RESET, RED, HIDDEN);
  va_start (arg, format);
  flag = vprintf (format, arg);
  va_end (arg);
  return flag;
}

int panicf(const char *format, ...) {
  int flag;
  va_list arg;
  textcolor (BRIGHT, MAGENTA, HIDDEN);
  printf ("MESSAGE: ");
  textcolor (RESET, MAGENTA, HIDDEN);
  va_start (arg, format);
  flag = vprintf (format, arg);
  va_end (arg);
  return flag;
}
