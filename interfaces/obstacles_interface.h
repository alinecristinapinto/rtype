#include <allegro5/allegro_primitives.h>

#ifndef PDS_TP1_RTYPE_OBSTACLES_INTERFACE_H
#define PDS_TP1_RTYPE_OBSTACLES_INTERFACE_H

#define NUM_ENEMIES 10
#define ENEMY_SPEED 8
#define BLOCK_SPEED 5;

typedef struct Block
{
	ALLEGRO_BITMAP *image;
	float x, y, sx, sy, width, height, moveX, moveY, moveSpeed;
} Block;

typedef enum EnemyTypeEnum { 
    GOUACHE,
    FENRIR,
    OLLIE
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
    GOUACHE_POSITION = 1,
    FENRIR_POSITION = 50,
    OLLIE_POSITION = 110
} EnemyTypePositionEnum;

typedef enum EnemyTypeWidthtEnum { 
    GOUACHE_WIDTH = 47,
    FENRIR_WIDTH = 50,
    OLLIE_WIDTH = 50
} EnemyTypeHWidthEnum;

typedef enum EnemyTypeHeightEnum { 
    GOUACHE_HEIGHT = 49,
    FENRIR_HEIGHT = 59,
    OLLIE_HEIGHT = 32
} EnemyTypeHeightEnum;

#endif
