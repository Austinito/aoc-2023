#include <stdio.h>
#include <stdlib.h>

#define MAX_GRID_WIDTH 100
#define MAX_GRID_HEIGHT 100

#define MAX_NUMBERS 50
#define MAX_SYMBOLS 50

typedef struct {
    int startX, endX;
    int y;
    int value;
} Number;

typedef struct {
    int x;
    int y;
    char symbol;
} Symbol;

void clearNumber(Number *n) {
    n->startX = -1;
    n->endX = -1;
    n->y = -1;
    n->value = -1;
}

Number *initNumbers() {
    Number *numbers = malloc(sizeof(Number) * MAX_NUMBERS);
    for (int i = 0; i < MAX_NUMBERS; i++) {
        clearNumber(&numbers[i]);
    }
    return numbers;
}

Symbol *initSymbols() {
    Symbol *symbols = malloc(sizeof(Symbol) * MAX_SYMBOLS);
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        symbols[i].x = -1;
        symbols[i].y = -1;
        symbols[i].symbol = ' ';
    }
    return symbols;
}

void loadGridData(FILE *fp, Number *numbers, Symbol *symbols) {
    int x = 0;
    int y = 0;
    int numNumbers = 0;
    int numSymbols = 0;

    char c;
    Number number = {-1, -1, -1, -1};
    Symbol symbol;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            x = 0;
            y++;
        } else if (c >= '0' && c <= '9') {
            if (number.startX == -1) {
                number.startX = x;
                number.endX = x;
                number.y = y;
                number.value = c - '0';
            } else {
                number.endX = x;
                number.value = number.value*10 + (c - '0');
            }
            x++;
        } else {
            if (number.startX != -1) {
                numbers[numNumbers] = number;
                numNumbers++;
                clearNumber(&number);
            }
            if (c != '.') {
                symbol.x = x;
                symbol.y = y;
                symbol.symbol = c;
                symbols[numSymbols] = symbol;
                numSymbols++;
            }
            x++;
        }
    }
}

// returns 1 if the number is a neighbor of the symbol, else 0
int isNeighbor(Number n, int x, int y) {
    int xMin = n.startX;
    if (xMin > 0) {
        xMin -= 1;
    }
    int xMax = n.endX;
    if (xMax < MAX_GRID_WIDTH - 1) {
        xMax += 1;
    }

    if (n.y == y) {
        if (x == xMin && x == xMax) {
            return 1;
        }
    } else if (n.y == (y + 1) || n.y == (y - 1)) {
        if (x >= xMin && x <= xMax) {
            return 1;
        }
    }

    if (n.value == 467) {
        printf("Number %d is not neighbor of (%d, %d)\n", n.value, x, y);
        printf("xMin: %d, xMax: %d\n", xMin, xMax);
    }
    return 0;
}

int addNumbers(Number *numbers, Symbol *symbols) {
    int result = 0;
    for (int i = 0; i < MAX_NUMBERS; i++) {
        if (numbers[i].startX == -1) {
            break;
        }
        // we could try to optmize by ridding of redundant checks
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            if (symbols[j].x == -1) {
                break;
            }
            if (isNeighbor(numbers[i], symbols[j].x, symbols[j].y)) {
                printf("Number %d is neighbor of symbol %d\n", i, j);
                result += numbers[i].value;

                printf("Result: %d\n", result);
                break;
            }
        }
    }
    return result;
}

int main(int argc, char const *argv[]) {

    if (argc != 2) {
        printf("Usage: ./day3 <input file>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    Number* numbers = initNumbers();
    Symbol* symbols = initSymbols();

    loadGridData(fp, numbers, symbols);


    int result = addNumbers(numbers, symbols);
/*
    // print out the numbers
    for (int i = 0; i < MAX_NUMBERS; i++) {
        if (numbers[i].startX == -1) {
            break;
        }
        printf("Number %d: %d with ([%d -> %d], %d)\n", i, numbers[i].value, numbers[i].startX, numbers[i].endX, numbers[i].y);
    }
    // print out the symbols
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (symbols[i].x == -1) {
            break;
        }
        printf("Symbol %d: %c at (%d, %d)\n", i, symbols[i].symbol, symbols[i].x, symbols[i].y);
    }
    */

    printf("Result: %d\n", result);

    return 0;
}

