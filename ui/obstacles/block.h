#include "../../interfaces/spaceship_interface.h"
#include "../../interfaces/obstacles_interface.h"

void initBlock(Block *block);

void updateBlock(Block *block);

void drawBlock(Block block);

int spaceshipAndBlockCollision(Spaceship spaceship, Block block);
