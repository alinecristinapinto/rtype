#include "../../interfaces/spaceship_interface.h"
#include "../../interfaces/obstacles_interface.h"

void initBlock(Block *block,  int screen_w, int screen_h);

void updateBlock(Block *block, int screen_w, int screen_h);

void drawBlock(Block block);

int spaceshipAndBlockCollision(Spaceship spaceship, Block block);
