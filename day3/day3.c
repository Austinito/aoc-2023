#include <stdio.h>
#include <stdlib.h>

#define MAX_GRID_WIDTH 150
#define MAX_GRID_HEIGHT 200

#define MAX_NUMBERS 2000
#define MAX_SYMBOLS 4000

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
        if (x == xMin || x == xMax) {
            return 1;
        }
    } else if (n.y == (y + 1) || n.y == (y - 1)) {
        if (x >= xMin && x <= xMax) {
            return 1;
        }
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
                result += numbers[i].value;
                break;
            }
        }
    }
    return result;
}

int getRatioForGear(Number *numbers, int x, int y) {
    int ratio = 0;
    int numNeighbors = 0;
    int neighborValue = 0;

    for (int j = 0; j < MAX_NUMBERS; j++) {
        if (numbers[j].startX == -1) {
            break;
        }
        if (isNeighbor(numbers[j], x, y)) {
            switch(numNeighbors){
                case 0:
                  neighborValue = numbers[j].value;
                  break;
                case 1:
                  ratio = neighborValue * numbers[j].value;
                  break;
                case 2:
                  return 0;
            }
            numNeighbors++;
        }
    }
    return ratio;
}

/* Returns the "gear ratio" of the grid
 * The gear ratio is whenever the '*' symbol is adjacent to EXACTLY 2 nubmers.
 * We then will multiply the two numbers together and add it to the result.
 * We do this for all the "gears" and add them all together.
 */
int getGearRatio(Number *numbers, Symbol *symbols) {
    int result = 0;

    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (symbols[i].x == -1) {
            break;
        }
        if (symbols[i].symbol == '*') {
            result += getRatioForGear(numbers, symbols[i].x, symbols[i].y);
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
    int gearRatio = getGearRatio(numbers, symbols);

    printf("Result: %d\n", result);
    printf("Gear Ratio: %d\n", gearRatio);

    return 0;
}

