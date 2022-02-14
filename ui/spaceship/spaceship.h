#include "../../interfaces/spaceship_interface.h"

// Spaceship
void initSpaceship(Spaceship *spaceship, int screen_h);

void updateSpaceship(Spaceship *spaceship, int screen_w, int screen_h);

void drawSpaceship(Spaceship spaceship);

void controlSpaceship(int keyCode, Spaceship *spaceship, Projectile *projectile, KeyEventsEnum keyEvent);

// Projectiles
void initProjectile(Projectile *projectile);

void shoot(Projectile *projectile, Spaceship *spaceship);

void updateProjectile(Projectile *projectile, int screen_w);

void drawProjectile(Projectile projectile);
