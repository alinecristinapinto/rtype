#include "../../interfaces/spaceship_interface.h"
#include "../../interfaces/obstacles_interface.h"
#include "../../interfaces/scenario_interface.h"

// Spaceship
void initSpaceship(Spaceship *spaceship);

void updateSpaceship(Spaceship *spaceship);

void drawSpaceship(Spaceship spaceship);

void controlSpaceship(int keyCode, Spaceship *spaceship, Projectile *projectile, KeyEventsEnum keyEvent);

// Projectiles
void initProjectile(Projectile *projectile, Spaceship spaceship);

void shoot(Projectile *projectile, Spaceship *spaceship);

void updateProjectile(Projectile *projectile, Spaceship spaceship);

void drawProjectile(Projectile projectile);

void handleCollisionBetweenProjectileAndEnemies(Projectile *projectile, Spaceship spaceship, Score *score, Enemy enemies[]);

void handleCollisionBetweenProjetileAndBlock(Projectile *projectile, Spaceship spaceship, Block block);
