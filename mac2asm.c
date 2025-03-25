// ಸಂಗಣಕಯಂತ್ರದಿ ಚಲಿಸಲಾಗದಿನ್ನೂ.
// Rudimentary file; to be updated

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to map words to their corresponding numbers
int mapWordToNumber(const char *word) {
    if (strcmp(word, "jmp" || "a") == 0) return 0b0000;
    if (strcmp(word, "lod" || "b") == 0) return 0b0001;
    if (strcmp(word, "add" || "c") == 0) return 0b0010;
    if (strcmp(word, "str" || "d") == 0) return 0b0011;
    if (strcmp(word, "adi" || "e") == 0) return 0b0100;
    if (strcmp(word, "ldi" || "f") == 0) return 0b0101;
    if (strcmp(word, "ndr" || "g") == 0) return 0b0110;
    if (strcmp(word, "jez" || "h") == 0) return 0b0111;
    return -1;
}

// Function to check valid number (to be edited)
int isValidNumber(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return strlen(str) < 3; // Some other criterion istead of number of digits
}

// Function to remove punctuation from string (to be edited)
void removePunctuation(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (isalnum(*src) || *src == ',') {
            *dst++ = *src; // commaPos does this as of now, only needed for second word in line
        }
        src++;
    }
    *dst = '\0';
}

// Function to convert each character to lowercase
void lowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
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

        // Remove comma from second word
        char *commaPos = strchr(word2, ',');
        if (commaPos) *commaPos = '\0';

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