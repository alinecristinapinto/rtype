#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "enemies.h"
#include "../../utils/constants.h"

EnemyTypeEnum sortEnemyType(){
    return (enum EnemyTypeEnum)(rand()%3); 
}

float getEnemyTypePosition(EnemyTypeEnum type){
    switch (type){
        case GOUACHE:
            return GOUACHE_POSITION;
        case FENRIR:
            return FENRIR_POSITION;
        case OLLIE:
            return OLLIE_POSITION;
        default:
            return GOUACHE_POSITION;
    }
}

float getEnemyTypeWidth(EnemyTypeEnum type){
    switch (type){
        case GOUACHE:
            return GOUACHE_WIDTH;
        case FENRIR:
            return FENRIR_WIDTH;
        case OLLIE:
            return OLLIE_WIDTH;
        default:
            return GOUACHE_WIDTH;
    }
}

float getEnemyTypeHeight(EnemyTypeEnum type){
    switch (type){
        case GOUACHE:
            return GOUACHE_HEIGHT;
        case FENRIR:
            return FENRIR_HEIGHT;
        case OLLIE:
            return OLLIE_HEIGHT;
        default:
            return GOUACHE_HEIGHT;
    }
}

void initEnemies(Enemy enemies[], ALLEGRO_BITMAP *image){
    for (int i = 0; i < NUM_ENEMIES; i++){
        enemies[i].id = i+1;
        enemies[i].image = image;
        enemies[i].type = sortEnemyType();
        enemies[i].sx = 0;
        enemies[i].sy = getEnemyTypePosition(enemies[i].type);
        enemies[i].width = getEnemyTypeWidth(enemies[i].type);
        enemies[i].height = getEnemyTypeHeight(enemies[i].type);
        enemies[i].moveSpeed = 1+rand()%ENEMY_SPEED;
        enemies[i].active = false;
    }
}

void releaseEnemies(Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(!enemies[i].active){
            if(rand()%100 == 0){
                enemies[i].x = SCREEN_W;
                enemies[i].y = rand()%(SCREEN_H-(int)enemies[i].height);
                enemies[i].active = true;
                break;
            }
        }
    }
}

void updateEnemies(Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active){
            enemies[i].x -= enemies[i].moveSpeed;
             
            if(enemies[i].x < 0) {
                enemies[i].active = 0;
            }
        }
    }
}

void drawEnemies(Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active){
            al_draw_bitmap_region(
                enemies[i].image,
                enemies[i].sx,
                enemies[i].sy,
                enemies[i].width,
                enemies[i].height,
                enemies[i].x,
                enemies[i].y, 
                0
            );
        }
    }
}

int hasCollisionBetweenEnemies(Enemy enemy1, Enemy enemy2){
    int xArea = (enemy1.x + enemy1.width) > enemy2.x && enemy1.x < (enemy2.x + enemy2.width);
    int yArea = (enemy1.y + enemy1.height) > enemy2.y && enemy1.y < (enemy2.y + enemy2.height);

    return xArea && yArea;
}

void handleCollisionBetweenEnemies(Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active){
            for (int j = 0; j < NUM_ENEMIES; j++){
                if(enemies[j].active &&  enemies[i].id != enemies[j].id){
                    if(hasCollisionBetweenEnemies(enemies[i], enemies[j])){
                        enemies[i].active = 0;
                        enemies[j].active = 0;
                    }
                }
            }
        }
    }
}

int hasCollisionBetweenEnemiesAndBlock(Enemy enemy1, Block block){
    int xArea = (enemy1.x + enemy1.width) > block.x && enemy1.x < (block.x + block.width);
    int yArea = (enemy1.y + enemy1.height) > block.y && enemy1.y < (block.y + block.height);

    return xArea && yArea;
}

void handleCollisionBetweenEnemiesAndBlock(Enemy enemies[], Block block){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active){
            if(hasCollisionBetweenEnemiesAndBlock(enemies[i], block)){
                enemies[i].active = 0;
            }
        }
    }
}

int spaceshipAndEnemiesCollision(Spaceship spaceship, Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active){
            int xArea = (spaceship.x + spaceship.width) > enemies[i].x &&
                         spaceship.x < (enemies[i].x + enemies[i].width);
            int yArea = (spaceship.y + spaceship.height) > enemies[i].y &&
                         spaceship.y < (enemies[i].y + enemies[i].height);

            if(xArea && yArea) {
                return 1;
            };
        }
    }

    return 0;
}
