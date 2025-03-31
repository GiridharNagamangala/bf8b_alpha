#include <stdio.h>
#include <ctype.h>

// Function to remove punctuation from string (to be edited)
// Yet to be called in main()
void removeComma(char *string) {
    char *src = string, *dst = string;
    while (*src) {
        if (isalnum(*src) || *src == ',') {
            *dst++ = *src; // Takes care of any punctuation to be removed
        }
        src++;
    }
    *dst = '\0';
}

void removeWhiteSpace(char *string) {
    char *src = string, *dst = string;
    while (*src) {
        if (*src == ' ') {
            *dst++ = *src; // Takes care of any whitespace to be removed
        }
        src++;
    }
    *dst = '\0';
}