#include <stdio.h>
#define MAXLINE 1000

void reverse(char rLine[]) {
  int i, j;
  char aux;
  for (i = 0; rLine[i] != '\0'; ++i)
    ;
  --i;
  if (rLine[i] == '\n')
  --i;
  j = 0;
  while (j < i) {
    aux = rLine[j];
    rLine[j] = rLine[i];
    rLine[i] = aux;
    --i;
    ++j;
  }
}

int readLines(char str[], int limit) {
  int i, c;
  for (i = 0; i < limit-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    str[i] = c;
  if (c == '\n') {
    str[i] = c;
    ++i;
  }
  str[i] = '\0';
  return i;
}

int main(int argc, char **argv){
    // Place your magic here
    int len;
    char line[MAXLINE];
    while ((len = readLines(line, MAXLINE)) > 0) {
      reverse(line);
      printf("%s\n", line);
    }
    return 0;
}
