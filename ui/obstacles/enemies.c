#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "enemies.h"

const int ENEMY_SPEED = 3;

EnemyTypeEnum sortEnemyType(){
    return BYDO_MINION_1;
}

void initEnemies(Enemy enemies[]){
    for (int i = 0; i < NUM_ENEMIES; i++){
        enemies[i].id = i+1;
        enemies[i].sx = 0;
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
            al_draw_filled_circle(enemies[i].x, enemies[i].y, 20, al_map_rgba_f(.6,0,.6,.6));
        }
    }
}
