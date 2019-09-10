#include <stdio.h>

#define MAXLINE 1000


void reverse(char readLine[])
{
  int i, j;
  char aux;

  for (i = 0; readLine[i] != '\0'; ++i)
    ;
  --i;
  if (readLine[i] == '\n')
  --i;
  j = 0;
  while (j < i) {
    aux = readLine[j];
    readLine[j] = readLine[i];
    readLine[i] = aux;
    --i;
    ++j;
  }
}

int getLines(char str[], int limit)
{
  int i, c;

  for (i = 0; i < limit-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    str[i] = c;
  if (c == '\n')
  {
    str[i] = c;
    ++i;
  }
  str[i] = '\0';
  return i;
}

int main(int argc, char **argv)
{
  // Place your magic here
  int len;
  char line[MAXLINE];

  while ((len = getLines(line, MAXLINE)) > 0)
  {
    reverse(line);
    printf("%s\n", line);
  }
  return 0;
}
