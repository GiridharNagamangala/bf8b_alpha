#include <stdio.h>
#include <ctype.h>

// Function to remove punctuation from string (to be edited)
// Yet to be called in main()
void removeWhiteSpace(char *string) {
    char *src = string, *dst = string;
    while (*src) {
        if (isalnum(*src) || *src == ',' || *src == ' ') {
            *dst++ = *src; // Takes care of any punctuation to be removed
        }
        src++;
    }
    *dst = '\0';
}