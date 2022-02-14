#ifndef PDS_TP1_RTYPE_SCENARIO_INTERFACE_H
#define PDS_TP1_RTYPE_SCENARIO_INTERFACE_H

#define NUM_STARS 50

typedef struct Star
{
    float x, y, radius, moveSpeed;
} Star;

typedef struct Score
{
    int score;
    int numerKilledBydoMinion1, numerKilledBydoMinion2, numerKilledBydoMinion3;
} Score;

#endif
