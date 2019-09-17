#include <stdio.h>

int mystrlen(char *str);
char *mystradd(char *origin, char *addition);
int mystrfind(char *origin, char *substr);

int main(int argc, char **argv) {
  if (argc < 4) {
    printf("Need to pass tree arguments\n");
    printf("How to execute option one: ./main <string> <string2> <subString>\n");
    return 1;
  }
  int lenght = mystrlen(argv[1]);
  char *stringAdd = mystradd(argv[1], argv[2]);
  int find = mystrfind(stringAdd, argv[3]);
  if (find = 1) {
    printf("Initial Lenght\t    : %d\nNew String\t    : %s\nSubString was found : yes\n", lenght, stringAdd);
  }
  else {
    printf("Initial Lenght\t    : %d\nNew String\t    : %s\nSubString was found : no\n", lenght, stringAdd);
  }
  return 0;
}
