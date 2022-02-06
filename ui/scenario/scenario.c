#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include "../../styles/colors.h"
#include "scenario.h"
#include <math.h>

void initStars(Star stars[], int screen_w, int screen_h, float moveSpeed){
    for (int i = 0; i < NUM_STARS; i++){
        stars[i].x = (rand() %screen_w) + screen_w;
        stars[i].y = rand() %screen_h;
        stars[i].radius = rand()%2;
        stars[i].moveSpeed = moveSpeed;
    }
}

void updateStars(Star stars[],  int screen_w){
    for (int i = 0; i < NUM_STARS; i++){
        stars[i].x -= stars[i].moveSpeed;

        if(stars[i].x < 0) {
            stars[i].x = screen_w;
        }
    }
}

void drawStars(Star stars[]){
    Colors colors = getColors();
    
    for (int i = 0; i < NUM_STARS; i++){
        al_draw_filled_circle(stars[i].x, stars[i].y, stars[i].radius, colors.WHITE);
    }
}
