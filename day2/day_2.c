#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GAME_LOG_SIZE 1000

static char *colors[] = {"red", "green", "blue"};

// 1 if possible, 0 if not
int assurePossible(int rCount, int gCount, int bCount, char *gameLog) {
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
                if (num > rCount) {
                    printf("Invalid red color count: %d (max: %d)\n", num, rCount);
                    return 0;
                }
                break;
            case 1:
                printf("checking green: %d\n", num);
                if (num > gCount) {
                    printf("Invalid green color count: %d (max: %d)\n", num, gCount);
                    return 0;
                }
                break;
            case 2:
                if (num > bCount) {
                    printf("Invalid blue color count: %d (max: %d)\n", num, bCount);
                    return 0;
                }
                break;
            default:
                printf("Invalid color: %s\n", color);
                return 0;
        }

/*        printf("Nice! color %s is valid\n", color);*/
/*        printf("(gameLog is pointing to: %c)\n\n", *gameLog);*/
    }
    return 1;
}

int main(int argc, char *argv[]) {
    // red is argv[1], green is argv[2], blue is argv[3]
    int rCount, gCount, bCount;
    char *gameLogs;

    if (argc != 5) {
        printf("Usage: ./day_2 <red_count> <green_count> <blue_count> <fileName>\n");
        return 1;
    } else {
        rCount = atoi(argv[1]);
        gCount = atoi(argv[2]);
        bCount = atoi(argv[3]);
        gameLogs = argv[4];
    }

    char buffer[MAX_GAME_LOG_SIZE];
    FILE *fp = fopen(gameLogs, "r");

    if (fp == NULL) {
        printf("Error opening file %s\n", gameLogs);
        return 1;
    }

    int gameId = 0, total = 0;

    while (fgets(buffer, MAX_GAME_LOG_SIZE, fp) != NULL) {

        // Increment game number
        gameId++;

        // Determine if game is possible
        if (assurePossible(rCount, gCount, bCount, buffer) == 1) {
            printf("Game %d: Possible\n", gameId);
            total += gameId;
        } else {
            printf("Game %d: Not possible\n", gameId);
        }
    }

    printf("Total: %d\n", total);

    return 0;
}
