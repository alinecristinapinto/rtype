#include <allegro5/allegro_primitives.h>

#ifndef PDS_TP1_RTYPE_OBSTACLES_INTERFACE_H
#define PDS_TP1_RTYPE_OBSTACLES_INTERFACE_H

#define NUM_ENEMIES 10

typedef struct Block
{
	ALLEGRO_BITMAP *image;
	float x, y, sx, sy, width, height, moveX, moveY, moveSpeed;
} Block;

typedef enum EnemyTypeEnum { BYDO_MINION_1, BYDO_MINION_2, BYDO_MINION_3 } EnemyTypeEnum;
// ZABTOM

typedef struct Enemy
{
    int id;
    EnemyTypeEnum type;
    int active;
	float x, y, sx, sy, moveSpeed;
} Enemy;

#endif
