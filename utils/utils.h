#ifndef PDS_TP1_RTYPE_UTILS_H
#define PDS_TP1_RTYPE_UTILS_H

#include "../interfaces/scenario_interface.h"

FILE* openFile(char* name, char* mode);
void closeFile(FILE* file);
void readGameHistory(FILE* file, Score *score);
void writeGameHistory(FILE* file, Score score);

#endif 
