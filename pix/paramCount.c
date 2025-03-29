#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int paramCount(char *string) {
    char *s = string, *count = string;
    while (*s) {if (*s == " ") count++;}
    return count;
}