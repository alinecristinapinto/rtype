#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "block.h"
#include "../../utils/constants.h"

void initBlock(Block *block){
    block->x = SCREEN_W + rand()%(SCREEN_W);
    block->y = rand()%(4*SCREEN_H/5);
    block->width = SCREEN_W + rand()%(SCREEN_W/2);
    block->height = SCREEN_H/5 + rand()%(2*SCREEN_H/5);
    block->sx = 0;
	block->sy = 0;
    block->moveSpeed = 2+rand()%BLOCK_SPEED;
}

void updateBlock(Block *block){
    block->x -= block->moveSpeed;

    if(block->x + block->width < 0){
        initBlock(block);
    }
}

void drawBlock(Block block){
    al_draw_bitmap_region(
        block.image,
        block.sx,
        block.sy,
        block.width,
        block.height,
        block.x,
        block.y, 
        0
    );
}

int spaceshipAndBlockCollision(Spaceship spaceship, Block block){
    int xArea = (spaceship.x + spaceship.width) > block.x && spaceship.x < (block.x + block.width);
    int yArea = (spaceship.y + spaceship.height) > block.y && spaceship.y < (block.y + block.height);

    return xArea && yArea;
}

