#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../interfaces/scenario_interface.h"

FILE* openFile(char* name, char* mode){
    FILE *fp;
    fp  = fopen(name, mode);

    return fp;
}

void closeFile(FILE* file){
    fclose(file);
}

void readGameHistory(FILE* file, Score *score){
    int scorePlayer = 0;

    char buffer[6];
    buffer[0] = '\0';

    fgets(buffer, 5, file);

    if(strlen(buffer) > 0){
        scorePlayer = atoi(strtok(buffer," "));
    }

    score->record = scorePlayer;
}

void writeGameHistory(FILE* file, Score score){
    char history[5];
    sprintf(history, "%d", score.score);
    fputs(history, file);
}

int hasBoundingBoxCollision(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2){
    int xArea = (x1 + width1) > x2 && x1 < (x2 + width2);
    int yArea = (y1 + height1) > y2 && y1 < (y2 + height2);

    return xArea && yArea;
}
