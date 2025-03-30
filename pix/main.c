// ಸಂಗಣಕಯಂತ್ರದಿ ಚಲಿಸಲಾಗದಿನ್ನೂ.
// Rudimentary file; to be updated

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "supf.h"

/*
Functions listed in supf header file
Function to map words to their corresponding numbers
Function to check valid number
Function to remove punctuation from string
Function to convert each character to lowercase
Function to convert immediates and addresses to binary
Function to count the number of words in a line
*/

int main() {

    int choice;
    printf("Mode of input [Enter number]:\nType 1 for Console/Terminal\nType 2 to Upload pippadix assembly file\n");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        printf("Enter valid choice\n");
        main();
    } else if (choice == 1) {
        // Code for console input
        // return 1 ಇದ್ದೆಲ್ಲೆಡೆ file close ಮಾಡದೆ, ಮರಳಿ user input ಪಡೆಯುವಂತಿರಬೇಕು
        printf("Enter all commands in lowercase\nType 'exit' to exit program\n\n");
        
        char outputFileName[] = "pix_dump";
        FILE *outputFile;
        char *userin;
        outputFile = fopen(outputFileName, "wb");
        
        while (userin != "exit") {
            printf(">\t");
            scanf("%s", userin);

            int num1, num2, num3, num4;
            int command = 0; // Binary word going here
            char delimiter[] = " ";
            char *temp;

            // Convert all characters to lowercase
            lowerCase(userin);

            temp = strtok(userin, delimiter); // Just extract the first word (for opcode)
            num1 = mapWordToNumber(temp);

            if (num1 == -1) { // catch wrong syntax
                fprintf(stderr, "Error: Syntax incorrect, word '%s'\n", temp);
                fclose(outputFile);
                return 1;
            }
            // Block for "add" and "ndr"
            else if (num1 == 0b0011 || num1 == 0b0110) {
                while(temp != NULL) {
                    if (mapWordToNumber(temp) == -1) {
                        fprintf(stderr, "Error: Syntax incorrect, word '%s'\n", temp);
                        fclose(outputFile);
                        return 1;
                    } else {
                        command += (command << 4) + mapWordToNumber(temp);
                        temp = strtok(NULL, delimiter);
                    }
                }
            }

            // Block for "lod", "str" and "jez"
            else if (num1 == 0b0001 || num1 == 0b0010 || num1 == 0b0111) {
                temp = strtok(NULL, delimiter);
                num2 = mapWordToNumber(temp);
                temp = strtok(NULL, delimiter);
                num3 = (int)temp; // Do I need binConverter.c?
                if (num2 == -1 || num3 >= 256 || num3 < 0) {
                    fprintf(stderr, "Adressing out of bound\n");
                    fclose(outputFile);
                    return 1;
                } else {
                    command += (num1 << 12) + (num2 << 8) + (num3);
                }
            }
            
            // Block for "jmp"
            else if (num1 == 0b0000) {
                temp = strtok(NULL, delimiter);
                num2 = (int)temp;
                if (num2 >= 256 || num2 < 0) {
                    fprintf(stderr, "Error: Adressing out of bound\n");
                    fclose(outputFile);
                    return 1;
                }
                command += (num1 << 12) + (num2);
            }

            // Block for "adi"
            else if (num1 == 0b0100) {
                temp = strtok(NULL, delimiter);
                num2 = mapWordToNumber(temp);
                temp = strtok(NULL, delimiter);
                num3 = mapWordToNumber(temp);
                temp = strtok(NULL, delimiter);
                num4 = (int)temp;
                if (num4 >= 16 || num4 < 0) {
                    fprintf(stderr, "Error: Adressing out of bound\n");
                    fclose(outputFile);
                    return 1;
                }
                command += (num1 << 12) + (num2 << 8) + (num3 << 4) + num4;
            }

            // Block for "ldi"
            else if (num1 == 0b0101) {
                temp = strtok(NULL, delimiter);
                num2 = mapWordToNumber(temp);
                temp = strtok(NULL, delimiter);
                num3 = (int)temp;
                if (num4 >= 256 || num4 < 0) {
                    fprintf(stderr, "Error: Adressing out of bound\n");
                    fclose(outputFile);
                    return 1;
                }
                command += (num1 << 12) + (num2 << 8) + num3;
            }

            // Need to write to outputFile, command by command
            // Need to account for comma (both removal and confirmation)
        }
        
        fclose(outputFile);

    } else if (choice == 2) {
        // Code for file upload
        char inputFileName[100], outputFileName[100];
        FILE *inputFile, *outputFile;
        char line[256];
        
        // Input file name from user (to be edited)
        printf("Enter the input file name: ");
        scanf("%s", inputFileName);
        
        // Open the input file in text read mode
        inputFile = fopen(inputFileName, "r");
        if (inputFile == NULL) {
            perror("Error opening input file");
            return 1;
        }

        // Output file name
        strcpy(outputFileName, inputFileName);
        strcat(outputFileName, "_bitstream");

        // Open the output file in binary write mode
        outputFile = fopen(outputFileName, "wb");
        if (outputFile == NULL) {
            perror("Error opening output file");
            fclose(inputFile);
            return 1;
        } // output file should be of binary (.bin) format

        while (fgets(line, sizeof(line), inputFile)) {
            // char *word1, *word2, *word3, *word4; // ಇವು ಬೇಕಿಲ್ಲವು ಈಗಿಂದಲಿ
            int num1, num2, num3, num4; // integer variables to collect nibbles

            // Just thinking aloud
            int command = 0; // Binary word going here
            int index = 0; // to count which line we're on
            char delimiter[] = " ";
            char *temp;

            // Convert all characters to lowercase
            lowerCase(line);

            temp = strtok(line, delimiter); // Just extract the first word (for opcode)
            num1 = mapWordToNumber(temp);

            if (num1 == -1) { // catch wrong syntax
                fprintf(stderr, "Error: Syntax incorrect, line %d word '%s'\n", index++ + 1, temp);
                fclose(inputFile);
                fclose(outputFile);
                return 1;
            }
            // Block for "add" and "ndr"
            else if (num1 == 0b0011 || num1 == 0b0110) {
                while(temp != NULL) {
                    if (mapWordToNumber(temp) == -1) {
                        fprintf(stderr, "Error: Syntax incorrect, line %d word '%s'\n", index + 1, temp);
                        fclose(inputFile);
                        fclose(outputFile);
                        return 1;
                    } else {
                        command += (command << 4) + mapWordToNumber(temp);
                        temp = strtok(NULL, delimiter);
                    }
                }
            }

            // Block for "lod", "str" and "jez"
            else if (num1 == 0b0001 || num1 == 0b0010 || num1 == 0b0111) {
                temp = strtok(NULL, delimiter);
                num2 = mapWordToNumber(temp);
                temp = strtok(NULL, delimiter);
                num3 = (int)temp; // Do I need binConverter.c?
                if (num2 == -1 || num3 >= 256 || num3 < 0) {
                    fprintf(stderr, "Error: Syntax incorrect, line %d\n", index + 1);
                    fclose(inputFile);
                    fclose(outputFile);
                    return 1;
                } else {
                    command += (num1 << 12) + (num2 << 8) + (num3);
                }
            }
            
            // Block for "jmp"
            else if (num1 == 0b0000) {
                temp = strtok(NULL, delimiter);
                num2 = (int)temp;
                if (num2 >= 256 || num2 < 0) {
                    fprintf(stderr, "Error: Syntax incorrect, line %d\n", index + 1);
                    fclose(inputFile);
                    fclose(outputFile);
                    return 1;
                }
                command += (num1 << 12) + (num2);
            }

            // Block for "adi"
            else if (num1 == 0b0100) {
                temp = strtok(NULL, delimiter);
                num2 = mapWordToNumber(temp);
                temp = strtok(NULL, delimiter);
                num3 = mapWordToNumber(temp);
                temp = strtok(NULL, delimiter);
                num4 = (int)temp;
                if (num4 >= 16 || num4 < 0) {
                    fprintf(stderr, "Error: Syntax incorrect, line %d\n", index + 1);
                    fclose(inputFile);
                    fclose(outputFile);
                    return 1;
                }
                command += (num1 << 12) + (num2 << 8) + (num3 << 4) + num4;
            }

            // Block for "ldi"
            else if (num1 == 0b0101) {
                temp = strtok(NULL, delimiter);
                num2 = mapWordToNumber(temp);
                temp = strtok(NULL, delimiter);
                num3 = (int)temp;
                if (num4 >= 256 || num4 < 0) {
                    fprintf(stderr, "Error: Syntax incorrect, line %d\n", index + 1);
                    fclose(inputFile);
                    fclose(outputFile);
                    return 1;
                }
                command += (num1 << 12) + (num2 << 8) + num3;
            }

            // Need to write to outputFile, command by command
            // Need to account for comma (both removal and confirmation)
        }
        // Close files
        fclose(inputFile);
        fclose(outputFile);

        printf("Processing complete. Results written to %s.\n", outputFileName);
    }
    return 0;
}
