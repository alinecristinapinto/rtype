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

void initScore(Score *score){
    score->score = 0;
    score->numerKilledBydoMinion1 = 0;
    score->numerKilledBydoMinion2 = 0;
    score->numerKilledBydoMinion3 = 0;
}

void drawScore(Score score, int screen_w, int screen_h, ALLEGRO_FONT *font){
    char scorePlayer[20];
    Colors colors = getColors();

    sprintf(scorePlayer, "Score: %d", score.score);

    al_draw_text(font, colors.WHITE, (0.5 * screen_w/15), screen_h/20, 0, scorePlayer);
}

