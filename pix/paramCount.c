#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int paramCount(char *string) {
    char *s = string;
    int count = 0;
    while (*s) {if (*s == ' ') count++;}
    return count;
}