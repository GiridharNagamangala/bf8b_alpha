#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to check valid number (to be edited)
int isValidNumber(const char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) return 0;
    }
    return strlen(string) < 3; // Some other criterion istead of number of digits
}