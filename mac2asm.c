// ಸಂಗಣಕಯಂತ್ರದಿ ಚಲಿಸಲಾಗದಿನ್ನೂ.
// Rudimentary file; to be updated

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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
int mapWordToNumber(const char word[50]) {
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

// Function to check valid number (to be edited)
int isValidNumber(const char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) return 0;
    }
    return strlen(string) < 3; // Some other criterion istead of number of digits
}

// Function to remove punctuation from string (to be edited)
// Yet to be called in main()
void removePunctuation(char *string) {
    char *src = string, *dst = string;
    while (*src) {
        if (isalnum(*src) || *src == ',' || *src == ' ') {
            *dst++ = *src; // Takes care of any punctuation to be removed
        }
        src++;
    }
    *dst = '\0';
}

// Function to convert each character to lowercase
void lowerCase(char *string) {
    for (int i = 0; string[i]; i++) {
        string[i] = tolower((unsigned char)string[i]);
    }
}

// Function to convert immediates and addresses to binary
// Yet to add code here I'm just lazy
int binnum = 0;
int binConverter(char *string) {
    if (string[1] == 'd') {}
    if (string[1] == 'h') {}
    if (string[1] == 'o') {}
}

int main() {
    char inputFileName[100], outputFileName[100];
    FILE *inputFile, *outputFile;
    char line[256];

    //Code for console input missing

    // Input file name from user (to be edited)
    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Output file name
    strcpy(outputFileName, inputFileName);
    strcat(outputFileName, "_bitstream");

    // Open the output file (to be edited)
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    } // output file should be of binary (.bin) format

    while (fgets(line, sizeof(line), inputFile)) {
        char word1[50], word2[50], word3[50];
        int num1, num2, num3;

        // Convert all characters to lowercase
        lowerCase(line);

        // Parse the line into words
        if (sscanf(line, "%49s %49s %49s", word1, word2, word3) != 3) {
            fprintf(stderr, "Error: Line does not contain exactly three words or is improperly formatted.\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        // Check if the second and third words are separated by a comma
        if (strchr(word2, ',') == NULL || strchr(word3, ',') != NULL) {
            fprintf(stderr, "Error: Missing comma between the second and third word.\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        // Map words to numbers or validate numbers
        num1 = mapWordToNumber(word1);
        if (num1 == -1 && !isValidNumber(word1)) {
            fprintf(stderr, "Error: Invalid word or number '%s' in the input.\n", word1);
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        num2 = mapWordToNumber(word2);
        if (num2 == -1 && !isValidNumber(word2)) {
            fprintf(stderr, "Error: Invalid word or number '%s' in the input.\n", word2);
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        num3 = mapWordToNumber(word3);
        if (num3 == -1 && !isValidNumber(word3)) {
            fprintf(stderr, "Error: Invalid word or number '%s' in the input.\n", word3);
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        // Write the results to the output file (to be edited)
        if (num1 != -1) {
            fprintf(outputFile, "%d ", num1);
        } else {
            fprintf(outputFile, "%s ", word1);
        }

        if (num2 != -1) {
            fprintf(outputFile, "%d\n", num2);
        } else {
            fprintf(outputFile, "%s\n", word2);
        }
    }

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    printf("Processing complete. Results written to %s.\n", outputFileName);
    return 0;
}