#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "spaceship.h"
#include "../../styles/colors.h"
#include "../../utils/constants.h"

void initSpaceship(Spaceship *spaceship){
	spaceship->x = 0;
	spaceship->y = SCREEN_H/2;
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

void updateSpaceship(Spaceship *spaceship){
    float moveX = spaceship->x + spaceship->moveX * spaceship->moveSpeed;
    float moveY = spaceship->y + spaceship->moveY * spaceship->moveSpeed;

    if(moveX <= 0) moveX = 0;
    if(moveX >= (SCREEN_W - spaceship->width)) moveX = (SCREEN_W - spaceship->width);
    if(moveY <= 0) moveY = 0;
    if(moveY >= (SCREEN_H - spaceship->height)) moveY = (SCREEN_H - spaceship->height);

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

void updateProjectile(Projectile *projectile, Spaceship spaceship){
    if(projectile->state.loading && projectile->radius <= MAX_PROJECTILE_RADIUS){
        projectile->radius += 0.20;
    }

    if(projectile->state.released){
        projectile->x += projectile->moveSpeed;
    } else {
        projectile->x = spaceship.x + spaceship.width + 10;
        projectile->y = spaceship.y + 17;
    }

    if(projectile->state.active && projectile->x > SCREEN_W){
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

void handleScore(Score *score, Enemy enemy){
    score->score += 2 * abs(enemy.moveSpeed) + (enemy.type * 4);
    score->numerKilledBydoMinion1 = enemy.type == BYDO_MINION_1 
                                    ? (score->numerKilledBydoMinion1+1) 
                                    : score->numerKilledBydoMinion1;
    score->numerKilledBydoMinion2 = enemy.type == BYDO_MINION_2 
                                    ? (score->numerKilledBydoMinion2+1) 
                                    : score->numerKilledBydoMinion2;
    score->numerKilledBydoMinion3 = enemy.type == BYDO_MINION_3 
                                    ? (score->numerKilledBydoMinion3+1) 
                                    : score->numerKilledBydoMinion3;
}

void handleCollisionBetweenProjectileAndEnemies(Projectile *projectile, Spaceship spaceship, Score *score, Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active  && projectile->state.released){
            if(hasCollisionBetweenProjectileAndEnemies(projectile, enemies[i])){
                enemies[i].active = 0;
                handleScore(score, enemies[i]);
                if(projectile->radius < MAX_PROJECTILE_RADIUS){
                    resetProjectile(projectile, spaceship);
                }
            } 
        }
    }
}

void handleCollisionBetweenProjetileAndBlock(Projectile *projectile, Spaceship spaceship, Block block){
    int xArea = projectile->x > block.x && projectile->x < (block.x + block.width);
    int yArea = projectile->y > block.y && projectile->y < (block.y + block.height);

    if(xArea && yArea){
        resetProjectile(projectile, spaceship);
    }
}
