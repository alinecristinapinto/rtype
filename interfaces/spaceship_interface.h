#include <allegro5/allegro_primitives.h>

#ifndef PDS_TP1_RTYPE_SPACESHIP_INTERFACE_H
#define PDS_TP1_RTYPE_SPACESHIP_INTERFACE_H

#define SPACESHIP_WIDTH 62;
#define SPACESHIP_HEIGHT 28;
#define SPACESHIP_SPEED 5;

typedef enum KeyEventsEnum { KEY_UP, KEY_DOWN } KeyEventsEnum;
enum SpaceshipSpriteSheetMovimentsEnum { TOP = 30, MIDDLE = 1, BOTTOM = 60 };

typedef struct Spaceship
{
	ALLEGRO_BITMAP *image;
	float x, y, sx, sy, width, height;
	float moveX, moveY, moveSpeed;
} Spaceship;

typedef struct Projectile
{
	int active;
	float x, y, radius, moveSpeed;
} Projectile;

#endif
