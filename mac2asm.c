// ಸಂಗಣಕಯಂತ್ರದಿ ಚಲಿಸಲಾಗದಿನ್ನೂ.
// Rudimentary file; to be updated

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "supf.h"

// Function to map words to their corresponding numbers

// Function to check valid number

// Function to remove punctuation from string

// Function to convert each character to lowercase

// Function to convert immediates and addresses to binary

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