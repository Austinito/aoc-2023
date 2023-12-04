#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int isDigit(char c) {
    return (c >= '0') && (c <= '9');
}

// Check if the given string is prepended to the input string
int isSpelledNumber(char *input, char *number, int length) {
    // check if the input string starts with the number
    for(int i = 0; i < length; i++) {
        if (input[i] != number[i]) {
            return 0;
        }
    }

    return 1;
}

// safely get a substring from a string
void getSub(char *input, int start, int length, char *output) {
    for(int i = 0; i < length; i++) {
        output[i] = input[start + i];
    }
}


// given a string, parse it into 2 numbers
int parseNumberForLine(char *input) {
    int firstNumber=10;
    int lastNumber=10;
    int found = 10;
    char subString[5];

    // loop through the string
    for(int i = 0; i < strlen(input); i++) {
        char c = input[i];
        switch(c) {
            case '0'...'9':
                found = input[i];
                break;
            case 'o':
                if (i + 2 < strlen(input)) {
                    getSub(input, i, 3, subString);
                    if (isSpelledNumber(subString, "one", 3) == 1) {
                        found = '1';
                    }
                }
                break;
            case 't':
                if (i + 4 < strlen(input)) {
                    getSub(input, i, 5, subString);
                    if (isSpelledNumber(subString, "two", 3) == 1) {
                        found = '2';
                    } else if (isSpelledNumber(subString, "three", 5) == 1) {
                        found = '3';
                    }
                } else if (i + 2 < strlen(input)) {
                    getSub(input, i, 3, subString);
                    if (isSpelledNumber(subString, "two", 3) == 1) {
                        found = '2';
                    }
                }
                break;
            case 'f':
                if (i + 3 < strlen(input)) {
                    getSub(input, i, 4, subString);
                    if (isSpelledNumber(subString, "four", 4) == 1) {
                        found = '4';
                    } else if (isSpelledNumber(subString, "five", 4) == 1) {
                        found = '5';
                    }
                }
                break;
            case 's':
                if (i + 4 < strlen(input)) {
                    getSub(input, i, 5, subString);
                    if (isSpelledNumber(subString, "six", 3) == 1) {
                        found = '6';
                    } else if (isSpelledNumber(subString, "seven", 5) == 1) {
                        found = '7';
                    }
                } else if (i + 2 < strlen(input)) {
                    getSub(input, i, 3, subString);
                    if (isSpelledNumber(subString, "six", 3) == 1) {
                        found = '6';
                    }
                }
                break;
            case 'e':
                if (i + 4 < strlen(input)) {
                    getSub(input, i, 5, subString);
                    if (isSpelledNumber(subString, "eight", 5) == 1) {
                        found = '8';
                    }
                }
                break;
            case 'n':
                if (i + 3 < strlen(input)) {
                    getSub(input, i, 4, subString);
                    if (isSpelledNumber(subString, "nine", 4) == 1) {
                        found = '9';
                    }
                }
                break;
            default:
                break;
        }
        // if digit found, save it in right spot
        if (found != 10) {
            if (firstNumber == 10) {
                firstNumber = found;
                lastNumber = found;
            } else {
                lastNumber = found;
            }
        }
        found = 10;
    }

    // concatenate the 2 numbers into a single string
    char *numberString = malloc(2);
    numberString[0] = firstNumber;
    numberString[1] = lastNumber;

    int result = atoi(numberString);

    printf("firstNumber: %d, lastNumber: %d, result: %d\n", firstNumber, lastNumber, result);

    return result;
}

int calculateTotal(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", fileName);
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int total = 0;

    // read the entire file into the buffer
    while ((read = getline(&line, &len, file)) != -1) {
        // to avoid segfaults, we need to make sure the buffer is big enough
        int result = parseNumberForLine(line);
        printf("line: %s: %d\n", line, result);
        total += result;
    }

    fclose(file);
    if (line) {
        free(line);
    }

    return total;
}

int main(int argc, char *argv[]) {
    // parse the input file (first argument)
    char *fileName = argv[1];

    int result = calculateTotal(fileName);

    printf("result: %d\n", result);

    return 0;
}

// We are going to be given a string, and we need to parse it into 2 numbers.
// The first digit is the first number in the string.
// The second digit is the last number in the string.
// All other characters are ignored.
// All digits in between are ignored.
//
// After all the numbers are parsed from the given strings, we need to add them together.
//
// We just learned that the strings can spell out the numbers, and we need to parse them.
