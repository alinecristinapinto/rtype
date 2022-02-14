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
        }
    }
}
