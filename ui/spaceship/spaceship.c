#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "spaceship.h"
#include "../../styles/colors.h"
#include "../../utils/constants.h"
#include "../../utils/utils.h"

void initSpaceship(Spaceship *spaceship){
    spaceship->image = al_load_bitmap("assets/img/spaceship.png");
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
                    projectile->state.loading = 1;
                }
            }
            if(keyEvent == KEY_UP) {
                projectile->state.loading = 0;
                projectile->state.active = 1;
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
    projectile->x = spaceship.x + spaceship.width + 2;
    projectile->y = spaceship.y + 17;
}

void resetProjectile(Projectile *projectile, Spaceship spaceship){
    initProjectile(projectile, spaceship);
}

void updateProjectile(Projectile *projectile, Spaceship spaceship){
    if(projectile->state.loading && projectile->radius <= MAX_PROJECTILE_RADIUS){
        projectile->radius += 0.1;
    }

    if(projectile->state.active){
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
    al_draw_filled_circle(projectile.x, projectile.y, projectile.radius, colors.CYAN);
}

int hasCollisionBetweenProjectileAndEnemies(Projectile *projectile, Enemy enemy){
    return hasBoundingBoxCollision(
        projectile->x,
        projectile->y,
        projectile->radius * 2,
        projectile->radius * 2,
        enemy.x,
        enemy.y,
        enemy.width,
        enemy.height
    );
}

void handleScore(Score *score, Enemy enemy){
    score->score += (4 * abs(enemy.moveSpeed) + (enemy.type * 4));
    score->numerKilledBydoMinion1 = enemy.type == GOUACHE 
                                    ? (score->numerKilledBydoMinion1+1) 
                                    : score->numerKilledBydoMinion1;
    score->numerKilledBydoMinion2 = enemy.type == FENRIR 
                                    ? (score->numerKilledBydoMinion2+1) 
                                    : score->numerKilledBydoMinion2;
    score->numerKilledBydoMinion3 = enemy.type == OLLIE 
                                    ? (score->numerKilledBydoMinion3+1) 
                                    : score->numerKilledBydoMinion3;
}

void handleCollisionBetweenProjectileAndEnemies(Projectile *projectile, Spaceship spaceship, Score *score, Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active  && projectile->state.active){
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
    int collision = hasBoundingBoxCollision(
        projectile->x,
        projectile->y,
        projectile->radius * 2,
        projectile->radius * 2,
        block.x,
        block.y,
        block.width,
        block.height
    );
    if(collision){
        resetProjectile(projectile, spaceship);
    }
}
