#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int endex(char* string) {
    int endest = 0;
    do { endest++;} while (string[endest] != '\0');
    return endest;
}