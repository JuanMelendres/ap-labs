#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mystrlen(char *str) {
  int lenght = 0;
  int i;
  for (i = 0; str[i] != 0; i++) {
    lenght++;
  }
  return lenght;
}

char *mystradd(char *origin, char *addition) {
  int originLen = mystrlen(origin);
  int addLen = mystrlen(addition);
  char *charAdd = malloc(sizeof(char)*originLen + addLen);
  strcpy(charAdd, origin);
  strcpy(charAdd + originLen, addition);
  return charAdd;
}

int mystrfind(char *origin, char *substr) {
  int i;
  int aux = 0;
  int originLen = mystrlen(origin);
  int subLen = mystrlen(substr);
  for (i = 0; i <= originLen; i++) {
    if (origin[i] == substr[0] && aux < 1) {
      aux++;
    }
    else if (origin[i] == substr[aux]) {
      aux++;
    }
    else {
      aux = 0;
    }
    if (aux >= subLen) {
      return 1;
    }
  }
  return 0;
}
