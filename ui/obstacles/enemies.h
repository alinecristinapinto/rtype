#include "../../interfaces/spaceship_interface.h"
#include "../../interfaces/obstacles_interface.h"

void initEnemies(Enemy enemies[], ALLEGRO_BITMAP *image);

void releaseEnemies(Enemy enemies[], int screen_w, int screen_h);

void updateEnemies(Enemy enemies[]);

void drawEnemies(Enemy enemies[]);

void handleCollisionBetweenEnemies(Enemy enemies[]);

void handleCollisionBetweenEnemiesAndBlock(Enemy enemies[], Block block);

int spaceshipAndEnemiesCollision(Spaceship spaceship, Enemy enemies[]);
