#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "spaceship.h"
#include "../../styles/colors.h"

void initSpaceship(Spaceship *spaceship, int screen_h){
	spaceship->x = 0;
	spaceship->y = screen_h/2;
	spaceship->sx = 0;
	spaceship->sy = MIDDLE;
	spaceship->width = SPACESHIP_WIDTH;
	spaceship->height = SPACESHIP_HEIGHT;
	spaceship->moveSpeed = SPACESHIP_SPEED;
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
    if(moveX >= (screen_w - spaceship->width)) moveX = (screen_w - spaceship->width);
    if(moveY <= 0) moveY = 0;
    if(moveY >= (screen_h - spaceship->height)) moveY = (screen_h - spaceship->height);

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
            if(keyEvent == KEY_DOWN) {
                if(!projectile->state.active){
                    projectile->state.active = 1;
                    projectile->state.loading = 1;
                }
            }
            if(keyEvent == KEY_UP) {
                projectile->state.loading = 0;
                projectile->state.released = 1;
            }
            break;
        default:
            break;
    }
}

void initProjectile(Projectile *projectile, Spaceship spaceship){
    projectile->radius = BASE_PROJECTILE_RADIUS;
    projectile->moveSpeed = 10;
    projectile->state.active = 0;
    projectile->state.loading = 0;
    projectile->state.released = 0;
    projectile->x = spaceship.x + spaceship.width + 5;
    projectile->y = spaceship.y + 17;
}

void resetProjectile(Projectile *projectile, Spaceship spaceship){
    initProjectile(projectile, spaceship);
}

void powerUpProjectile(Projectile *projectile, Spaceship spaceship){
    projectile->radius += 0.20;
    projectile->x = spaceship.x + spaceship.width + 10;
    projectile->y = spaceship.y + 17;
}

void updateProjectile(Projectile *projectile, Spaceship spaceship, int screen_w){
    if(projectile->state.loading && projectile->radius <= MAX_PROJECTILE_RADIUS){
        powerUpProjectile(projectile, spaceship);
    }

    if(projectile->state.released){
        projectile->x += projectile->moveSpeed;
    }

    if(projectile->state.active && projectile->x > screen_w){
        resetProjectile(projectile, spaceship);
    }
}

void drawProjectile(Projectile projectile){
    Colors colors = getColors();

    if(projectile.state.active){
        al_draw_filled_circle(projectile.x, projectile.y, projectile.radius, colors.CYAN);
    }
}

int hasCollisionBetweenProjectileAndEnemies(Projectile *projectile, Enemy enemy){
    int xArea = projectile->x > enemy.x && projectile->x < (enemy.x + enemy.width);
    int yArea = projectile->y > enemy.y && projectile->y < (enemy.y + enemy.height);

    return xArea && yArea;
}

void projectileAndEnemiesCollision(Projectile *projectile, Spaceship spaceship, Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(projectile->state.active && enemies[i].active){
            if(hasCollisionBetweenProjectileAndEnemies(projectile, enemies[i])){
                enemies[i].active = 0;
                if(projectile->radius < MAX_PROJECTILE_RADIUS){
                    resetProjectile(projectile, spaceship);
                }
            }
        }
    }
}
