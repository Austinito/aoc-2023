#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// given a string, parse it into 2 numbers
int day1(char *input) {
    int firstNumber=10;
    int lastNumber=10;

    // loop through the string
    for(int i = 0; i < strlen(input); i++) {
        // if the character is a digit
        if (input[i] >= '0' && input[i] <= '9') {
            // if the first number is null
            if (firstNumber == 10) {
                // set the first number to the digit
                firstNumber = input[i];
                lastNumber = input[i];
            } else {
                // set the second number to the digit
                lastNumber = input[i];
            }
        }
    }

    // concatenate the 2 numbers into a single string
    char *numberString = malloc(2);
    numberString[0] = firstNumber;
    numberString[1] = lastNumber;

    return atoi(numberString);
}

void readFile(char *fileName, char *buffer) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", fileName);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // read the entire file into the buffer
    while ((read = getline(&line, &len, file)) != -1) {
        // to avoid segfaults, we need to make sure the buffer is big enough
        strcat(buffer, line);
    }

    fclose(file);
    if (line) {
        free(line);
    }
}

int calculateTotal(char *buffer) {
    int total = 0;

    // loop through the buffer as a set of lines
    // each line is a string
    // each string should be parsed into 2 numbers
    // each number should be added to the total
    // the total should be printed and returned
    char *line = strtok(buffer, "\n");

    while (line != NULL) {
        int result = day1(line);
        printf("line: %s\n result: %d\n", result);
        total += result;
        line = strtok(NULL, "\n");
    }

    return total;
}

int main(int argc, char *argv[]) {
    // parse the input file (first argument)
    char *fileName = argv[1];

    // read the file into a buffer
    char buffer[1000000] = "";
    readFile(fileName, buffer);

    int result = calculateTotal(buffer);

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
