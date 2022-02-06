#include <allegro5/allegro_primitives.h>

typedef enum KeyEventsEnum { KEY_UP, KEY_DOWN } KeyEventsEnum;
enum SpriteSheetMovimentsEnum { TOP = 42, MIDDLE = 6, BOTTOM = 83 };

typedef struct Spaceship
{
	ALLEGRO_BITMAP *image;
	float x, y, sx, sy, width, height, moveX, moveY, moveSpeed;
} Spaceship;

typedef struct Projectile
{
	int active;
	float x, y, radius, moveSpeed;
} Projectile;

// Spaceship
void initSpaceship(Spaceship *spaceship, int screen_h);

void updateSpaceship(Spaceship *spaceship, int screen_w, int screen_h);

void drawSpaceship(ALLEGRO_BITMAP *image, Spaceship spaceship);

void controlSpaceship(int keyCode, Spaceship *spaceship, Projectile *projectile, KeyEventsEnum keyEvent);

// Projectiles
void initProjectile(Projectile *projectile);

void shoot(Projectile *projectile, Spaceship *spaceship);

void updateProjectile(Projectile *projectile, int screen_w);

void drawProjectile(Projectile projectile);
