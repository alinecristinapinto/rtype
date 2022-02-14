#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "enemies.h"

EnemyTypeEnum sortEnemyType(){
    return (enum EnemyTypeEnum)(rand()%3); 
}

float sortEnemyTypePosition(EnemyTypeEnum type){
    switch (type){
        case BYDO_MINION_1:
            return BYDO_MINION_1_POSITION;
        case BYDO_MINION_2:
            return BYDO_MINION_2_POSITION;
        case BYDO_MINION_3:
            return BYDO_MINION_3_POSITION;
        default:
            return BYDO_MINION_1_POSITION;
    }
}

float sortEnemyTypeWidth(EnemyTypeEnum type){
    switch (type){
        case BYDO_MINION_1:
            return BYDO_MINION_1_WIDTH;
        case BYDO_MINION_2:
            return BYDO_MINION_2_WIDTH;
        case BYDO_MINION_3:
            return BYDO_MINION_3_WIDTH;
        default:
            return BYDO_MINION_1_WIDTH;
    }
}

float sortEnemyTypeHeight(EnemyTypeEnum type){
    switch (type){
        case BYDO_MINION_1:
            return BYDO_MINION_1_HEIGHT;
        case BYDO_MINION_2:
            return BYDO_MINION_2_HEIGHT;
        case BYDO_MINION_3:
            return BYDO_MINION_3_HEIGHT;
        default:
            return BYDO_MINION_1_HEIGHT;
    }
}

void initEnemies(Enemy enemies[], ALLEGRO_BITMAP *image){
    for (int i = 0; i < NUM_ENEMIES; i++){
        enemies[i].id = i+1;
        enemies[i].image = image;
        enemies[i].type = sortEnemyType();
        enemies[i].sx = 0;
        enemies[i].sy = sortEnemyTypePosition(enemies[i].type);
        enemies[i].width = sortEnemyTypeWidth(enemies[i].type);
        enemies[i].height = sortEnemyTypeHeight(enemies[i].type);
        enemies[i].moveSpeed = 1+rand()%ENEMY_SPEED;
        enemies[i].active = false;
    }
}

void releaseEnemies(Enemy enemies[], int screen_w, int screen_h){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(!enemies[i].active){
            if(rand()%100 == 0){
                enemies[i].x = screen_w;
                enemies[i].y = 30+rand()%(screen_h-60);
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

            al_draw_filled_rectangle(enemies[i].x,
                             enemies[i].y,
                             enemies[i].x+enemies[i].width,
                             enemies[i].y+enemies[i].height,
                             al_map_rgba_f(.6,0,.6,.6));
        }
    }
}

int hasCollsionBetweenEnemies(Enemy enemy1, Enemy enemy2){
    int xArea = (enemy1.x + enemy1.width) > enemy2.x && enemy1.x < (enemy2.x + enemy2.width);
    int yArea = (enemy1.y + enemy1.height) > enemy2.y && enemy1.y < (enemy2.y + enemy2.height);

    return xArea && yArea;
}

void handleCollsionBetweenEnemies(Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active){
            for (int j = 0; j < NUM_ENEMIES; j++){
                if(enemies[j].active &&  enemies[i].id != enemies[j].id){
                    if(hasCollsionBetweenEnemies(enemies[i], enemies[j])){
                        enemies[i].active = 0;
                        enemies[j].active = 0;
                    }
                }
            }
        }
    }
}

int hasCollsionBetweenEnemiesAndBlock(Enemy enemy1, Block block){
    int xArea = (enemy1.x + enemy1.width) > block.x && enemy1.x < (block.x + block.width);
    int yArea = (enemy1.y + enemy1.height) > block.y && enemy1.y < (block.y + block.height);

    return xArea && yArea;
}

void handleCollsionBetweenEnemiesAndBlock(Enemy enemies[], Block block){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active){
            if(hasCollsionBetweenEnemiesAndBlock(enemies[i], block)){
                enemies[i].active = 0;
            }
        }
    }
}

int spaceshipAndEnemiesCollsion(Spaceship spaceship, Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        if(enemies[i].active){
            int xArea = (spaceship.x + spaceship.width) > enemies[i].x && spaceship.x < (enemies[i].x + enemies[i].width);
            int yArea = (spaceship.y + spaceship.height) > enemies[i].y && spaceship.y < (enemies[i].y + enemies[i].height);

            if(xArea && yArea) {
                printf("Colidiu\n");
                return 1;
            };
        }
    }

    return 0;
}
