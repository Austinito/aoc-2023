#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GAME_LOG_SIZE 1000

static char *colors[] = {"red", "green", "blue"};

void findMins(int *rCount, int *gCount, int *bCount, char *gameLog) {
    strsep(&gameLog, ":");

    int colorInd = 0, num = 0;
    char colorStart[6];
    while (*gameLog != '\0' && *gameLog != '\n') {
/*        printf("getting next: %s", gameLog);*/
        // skip whitespace
        while (*gameLog - '0' < 0 || *gameLog - '0' > 9) {
            gameLog++;
        }
        // read number
        num = 0;
        while (*gameLog != ' ') {
            num *= 10;
            num += *gameLog - '0';
            gameLog++;
        }
        gameLog++; // Skip space

        // read color
        char *color = colorStart;
        while (*gameLog - 'a' >= 0 && *gameLog - 'a' <= 25) {
            *color = *gameLog;
            color++;
            gameLog++;
        }
        *color = '\0';
        color = colorStart;

        // Check if color is valid
        for (colorInd = 0; colorInd < 3; colorInd++) {
            if (strcmp(colors[colorInd], color) == 0) {
                break;
            }
        }

        // verify the color count is less than given
        switch(colorInd) {
            case 0:
                if (num > *rCount) {
                    *rCount = num;
                }
                break;
            case 1:
                if (num > *gCount) {
                    *gCount = num;
                }
                break;
            case 2:
                if (num > *bCount) {
                    *bCount = num;
                }
                break;
            default:
                printf("Invalid color: %s\n", color);
                return;
        }
    }
}

int main(int argc, char *argv[]) {
    // red is argv[1], green is argv[2], blue is argv[3]
    int rCount = 0, gCount = 0, bCount = 0;
    char *gameLogs;

    if (argc != 2) {
        printf("Usage: ./day_2 file\n");
        return 1;
    } else {
        gameLogs = argv[1];
    }

    char buffer[MAX_GAME_LOG_SIZE];
    FILE *fp = fopen(gameLogs, "r");

    if (fp == NULL) {
        printf("Error opening file %s\n", gameLogs);
        return 1;
    }

    int gameId = 0, total = 0;

    printf("Starting values: red: %d, green: %d, blue: %d\n", rCount, gCount, bCount);

    while (fgets(buffer, MAX_GAME_LOG_SIZE, fp) != NULL) {
        // Increment game number
        gameId++;
        // Determine if game is possible
        findMins(&rCount, &gCount, &bCount, buffer);

        total += rCount * gCount * bCount;

        printf("Game %d: red: %d, green: %d, blue: %d\n", gameId, rCount, gCount, bCount);
        printf("Product: %d\n\n", rCount * gCount * bCount);
        // Reset counts
        rCount = 0;
        gCount = 0;
        bCount = 0;
    }

    printf("Total: %d\n", total);

    return 0;
}
