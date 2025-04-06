#include <stdio.h>
#include <string.h>

void reverser(char* string) {
    int i= 0, j = strlen(string) - 1;
    while (i < j) {
        char temp = string[i];
        string[i] = string[j];
        string[j] = temp;
        i++;
        j--;
    }
}

void itoa(int num, char* string, int base) {
    int i = 0, isNeg = 0;

    if (num == 0) {
        string[i++] = '0';
        string[i] = '\0';
        return;
    }

    if (num < 0 && base == 10) {
        isNeg = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        string[i++] = (rem > 9) ? (rem - 10 + 'a') : rem + '0';
        num /= base;
    }

    if (isNeg) {string[i++] = '-';}

    string[i] = '\0';
    reverser(string);
}