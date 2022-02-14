#include <allegro5/allegro_primitives.h>

#ifndef PDS_TP1_RTYPE_OBSTACLES_INTERFACE_H
#define PDS_TP1_RTYPE_OBSTACLES_INTERFACE_H

typedef struct Block
{
	ALLEGRO_BITMAP *image;
	float x, y, sx, sy, width, height, moveX, moveY, moveSpeed;
} Block;

#endif
