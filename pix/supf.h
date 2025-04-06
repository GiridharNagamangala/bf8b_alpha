#ifndef SUPF_H
#define SUPF_H

void lowerCase(char *string);
void removeComma(char *string);
void removeWhiteSpace(char *string);
int paramCount(char *string);
int isValidNumber(const char *string);
int mapWordToNumber(const char word[50]);
void convert_base(char *input, int base_in, int base_out, char *output);
int binConverter(char *string);
int endex(char* string);
void reverser(char* string);
void itoa(int num, char* string, int base);

#endif