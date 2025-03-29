#include <stdio.h>
#include <ctype.h>

// Function to convert each character to lowercase
void lowerCase(char *string) {
    for (int i = 0; string[i]; i++) {
        string[i] = tolower((unsigned char)string[i]);
    }
}