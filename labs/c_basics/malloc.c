#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *q = NULL;
    char *p = NULL;

    printf("Requesting space for \"Goodbye\"\n");
    q = (char *)malloc(strlen("Goodbye")+1);
    p = (char *)malloc(strlen("Goodbye")+1);

    printf("About to copy \"Goodbye\" to q at address %u\n", q);
    strcpy(q, "Goodbye");
    strcpy(p, "Goodbye");
    strcpy(q, "ewfhbbefkqjfknfqwkejbdqwljnldjqwnoiqwiqoqjnGoodbye");

    printf("Strings copied\n");
    printf("q = %s\n", q);
    printf("p = %s\n", p);

    return 0;

}
