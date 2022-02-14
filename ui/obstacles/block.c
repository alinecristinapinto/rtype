#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "block.h"

const int BLOCK_SY = 2;
const int BLOCK_SPEED = 5;

void initBlock(Block *block, int screen_w, int screen_h){
    block->x = screen_w + rand()%(screen_w);
    block->y = rand()%(4*screen_h/5);
    block->width = screen_w + rand()%(screen_w/2);
    block->height = screen_h/5 + rand()%(2*screen_h/5);
    block->sx = 0;
	block->sy = BLOCK_SY;
    block->moveSpeed = BLOCK_SPEED;
}

void updateBlock(Block *block, int screen_w, int screen_h){
    block->x -= block->moveSpeed;

    if(block->x + block->width < 0){
        initBlock(block, screen_w, screen_h);
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

int spaceshipAndBlockCollsion(Spaceship spaceship, Block block){
    int xArea = (spaceship.x + spaceship.width) > block.x && spaceship.x < (block.x + block.width);
    int yArea = (spaceship.y + spaceship.height) > block.y && spaceship.y < (block.y + block.height);

    return xArea && yArea;
}
