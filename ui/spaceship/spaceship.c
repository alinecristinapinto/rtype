#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "spaceship.h"
#include "../../styles/colors.h"

const int SPACESHIP_WIDTH = 62;
const int SPACESHIP_HEIGHT = 28;
const int SPACESHIP_SPEED = 5;

void initSpaceship(Spaceship *spaceship, int screen_h){
	spaceship->x = 0;
	spaceship->y = screen_h/2;
	spaceship->sx = 0;
	spaceship->sy = MIDDLE;
	spaceship->width = SPACESHIP_WIDTH;
	spaceship->height = SPACESHIP_HEIGHT;
	spaceship->moveSpeed = SPACESHIP_SPEED;
    spaceship->bx = spaceship->width;
    spaceship->by = spaceship->height;
}

void drawSpaceship(Spaceship spaceship){
    al_draw_bitmap_region(
        spaceship.image,
        spaceship.sx,
        spaceship.sy,
        spaceship.width,
        spaceship.height,
        spaceship.x,
        spaceship.y, 
        0
    );
}

void updateSpaceship(Spaceship *spaceship, int screen_w, int screen_h){
    float moveX = spaceship->x + spaceship->moveX * spaceship->moveSpeed;
    float moveY = spaceship->y + spaceship->moveY * spaceship->moveSpeed;

    if(moveX <= 0) moveX = 0;
    if(moveX >= (screen_w - SPACESHIP_WIDTH)) moveX = (screen_w - SPACESHIP_WIDTH);
    if(moveY <= 0) moveY = 0;
    if(moveY >= (screen_h - SPACESHIP_HEIGHT)) moveY = (screen_h - SPACESHIP_HEIGHT);

    spaceship->x = moveX;
    spaceship->y = moveY;
}

void controlSpaceship(int keycode, Spaceship *spaceship, Projectile *projectile, KeyEventsEnum keyEvent){
    switch (keycode){
        case ALLEGRO_KEY_W:
            spaceship->sy = TOP;
            if(keyEvent == KEY_UP) {
                spaceship->moveY ++;
                spaceship->sy = MIDDLE;
            }
            if(keyEvent == KEY_DOWN) spaceship->moveY --;
            break;
        case ALLEGRO_KEY_S:
            spaceship->sy = BOTTOM;
            if(keyEvent == KEY_UP) {
                spaceship->moveY --;
                spaceship->sy = MIDDLE;
            }
            if(keyEvent == KEY_DOWN) spaceship->moveY ++;
            break;
        case ALLEGRO_KEY_A:
            spaceship->sy = MIDDLE;
            if(keyEvent == KEY_UP) spaceship->moveX ++;
            if(keyEvent == KEY_DOWN) spaceship->moveX --;
            break;
        case ALLEGRO_KEY_D:
            spaceship->sy = MIDDLE;
            if(keyEvent == KEY_UP) spaceship->moveX --;
            if(keyEvent == KEY_DOWN) spaceship->moveX ++;
            break;
        case ALLEGRO_KEY_SPACE:
            if(keyEvent == KEY_DOWN) shoot(projectile, spaceship);
            break;
        default:
            break;
    }
}

void initProjectile(Projectile *projectile){
    projectile->moveSpeed = 10;
    projectile->radius = 10;
    projectile->active = false;
}

void shoot(Projectile *projectile, Spaceship *spaceship){
    if(!projectile->active){
        projectile->x = spaceship->x + SPACESHIP_WIDTH - 15;
        projectile->y = spaceship->y + 15;
        projectile->active = true;
    }
}

void updateProjectile(Projectile *projectile, int screen_w){
    projectile->x += projectile->moveSpeed;

    if(projectile->x > screen_w){
        projectile->active = false;
    }
}

void drawProjectile(Projectile projectile){
    Colors colors = getColors();

    if(projectile.active){
        al_draw_filled_circle(projectile.x, projectile.y, projectile.radius, colors.MEDIUM_VIOLET_RED);
    }
}
