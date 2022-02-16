#ifndef PDS_TP1_RTYPE_UTILS_H
#define PDS_TP1_RTYPE_UTILS_H

#include "../interfaces/scenario_interface.h"

FILE* openFile(char* name, char* mode);
void closeFile(FILE* file);
void readGameHistory(FILE* file, Score *score);
void writeGameHistory(FILE* file, Score score);
int hasBoundingBoxCollision(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);

#endif 
