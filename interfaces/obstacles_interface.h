#include <allegro5/allegro_primitives.h>

#ifndef PDS_TP1_RTYPE_OBSTACLES_INTERFACE_H
#define PDS_TP1_RTYPE_OBSTACLES_INTERFACE_H

#define NUM_ENEMIES 10
#define ENEMY_WIDTH 51;
#define ENEMY_HEIGHT 143;
#define ENEMY_SPEED 3

typedef struct Block
{
	ALLEGRO_BITMAP *image;
	float x, y, sx, sy, width, height, moveX, moveY, moveSpeed;
} Block;

typedef enum EnemyTypeEnum { 
    BYDO_MINION_1,
    BYDO_MINION_2,
    BYDO_MINION_3
} EnemyTypeEnum;

typedef struct Enemy
{
    int id;
    EnemyTypeEnum type;
    ALLEGRO_BITMAP *image;
    int active;
	float x, y, sx, sy, width, height, moveSpeed;
} Enemy;

typedef enum EnemyTypePositionEnum {
    BYDO_MINION_1_POSITION = 1,
    BYDO_MINION_2_POSITION = 50,
    BYDO_MINION_3_POSITION = 110
} EnemyTypePositionEnum;

typedef enum EnemyTypeWidthtEnum { 
    BYDO_MINION_1_WIDTH = 47,
    BYDO_MINION_2_WIDTH = 50,
    BYDO_MINION_3_WIDTH = 50
} EnemyTypeHWidthEnum;

typedef enum EnemyTypeHeightEnum { 
    BYDO_MINION_1_HEIGHT = 49,
    BYDO_MINION_2_HEIGHT = 59,
    BYDO_MINION_3_HEIGHT = 32
} EnemyTypeHeightEnum;

// ZABTOM

#endif
