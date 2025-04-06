#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "supf.h"

void convert_base(char *input, int base_in, int base_out, char *output) {
    // Step 0: Get rid of punctuation and alphanumericals
    int endie = endex(input);
    if (input[3] == '\'') {input += 3;}
    if (isalpha(input[endie])) {input[endie - 1] = '\0';}
    
    // Step 1: Convert input string (base_in) to long int
    char *endptr;
    long num = strtol(input, &endptr, base_in);

    // Step 2: Convert num to output string (base_out)
    if (base_out == 10) {
        sprintf(output, "%ld", num);  // Fast path for decimal
    } else {
        // Custom logic for other bases (e.g., base 2, 8, 16)
        char *ptr = output;
        if (num == 0) {
            *ptr++ = '0';
        } else {
            while (num > 0) {
                int digit = num % base_out;
                *ptr++ = (digit < 10) ? digit + '0' : digit - 10 + 'A';
                num /= base_out;
            }
        }
        *ptr = '\0';
        // Reverse the string (digits are generated in reverse order)
        for (int i = 0, j = strlen(output) - 1; i < j; i++, j--) {
            char tmp = output[i];
            output[i] = output[j];
            output[j] = tmp;
        }
    }
}

// Function to convert immediates and addresses to binary
// Idea is to interpret base using any affix: 0x'-/-h, 0d'-/-d, 0o'-/-o or 0b'-/-b
// Yet to add code here I'm just lazy
int binConverter(char *string) {
    char *outnum;
    int i = endex(string);
    if (string[1] == 'x' || string[i] == 'h') {convert_base(string, 16, 10, outnum);}
    if (string[1] == 'd' || string[i] == 'd') {convert_base(string, 10, 10, outnum);}
    if (string[1] == 'o' || string[i] == 'o') {convert_base(string, 8, 10, outnum);}
    if (string[1] == 'b' || string[i] == 'b') {convert_base(string, 2, 10, outnum);}
    return atoi(outnum);
}