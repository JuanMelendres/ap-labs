#include <stdio.h>
#include <string.h>

char *foo(char *p) {
    char q[strlen(p)+1];
    strcpy(q, p);
    printf("From q: the string is %s\n", q);
    return q;
}

int main() {
    char *a = NULL;
    char *b = NULL;

    a = foo("Hi there, Chris");
    b = foo("Goodbye");
    printf("From main: %s %s\n", a, b);
    return 0;
}
