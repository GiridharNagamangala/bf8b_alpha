#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Commented out but just in case I need it later
// char jmp[3] = "jmp"; char a[2] = "a";
// char lod[3] = "lod"; char b[2] = "b";
// char add[3] = "add"; char c[2] = "c";
// char str[3] = "str"; char d[2] = "d";
// char adi[3] = "adi"; char e[2] = "e";
// char ldi[3] = "ldi"; char f[2] = "f";
// char ndr[3] = "ndr"; char g[2] = "g";
// char jez[3] = "jez"; char h[2] = "h";

// Function to map words to their corresponding numbers
int mapWordToNumber(const char *word) {
    if (strcmp(word, "jmp") == 0 || strcmp(word, "a") == 0) return 0b0000;
    if (strcmp(word, "lod") == 0 || strcmp(word, "b") == 0) return 0b0001;
    if (strcmp(word, "add") == 0 || strcmp(word, "c") == 0) return 0b0010;
    if (strcmp(word, "str") == 0 || strcmp(word, "d") == 0) return 0b0011;
    if (strcmp(word, "adi") == 0 || strcmp(word, "e") == 0) return 0b0100;
    if (strcmp(word, "ldi") == 0 || strcmp(word, "f") == 0) return 0b0101;
    if (strcmp(word, "ndr") == 0 || strcmp(word, "g") == 0) return 0b0110;
    if (strcmp(word, "jez") == 0 || strcmp(word, "h") == 0) return 0b0111;
    return -1;
}