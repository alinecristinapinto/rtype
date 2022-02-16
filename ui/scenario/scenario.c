#include <stdio.h>
#include <math.h>
#include "scenario.h"
#include <allegro5/allegro_primitives.h>
#include "../../styles/colors.h"
#include "../../utils/constants.h"

void initStars(Star stars[], float moveSpeed){
    for (int i = 0; i < NUM_STARS; i++){
        stars[i].x = (rand() %SCREEN_W) + SCREEN_W;
        stars[i].y = rand() %SCREEN_H;
        stars[i].radius = rand()%2;
        stars[i].moveSpeed = moveSpeed;
    }
}

void updateStars(Star stars[]){
    for (int i = 0; i < NUM_STARS; i++){
        stars[i].x -= stars[i].moveSpeed;

        if(stars[i].x < 0) {
            stars[i].x = SCREEN_W;
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
    score->record = 0;
    score->newRecord = 0;
    score->numerKilledBydoMinion1 = 0;
    score->numerKilledBydoMinion2 = 0;
    score->numerKilledBydoMinion3 = 0;
}

void updateScore(Score *score){
    if(score->score > score->record){
        score->record = score->score;
        score->newRecord = 1;
    }
}

void drawScore(Score score, ALLEGRO_FONT *font22){
    char scorePlayer[20];
    Colors colors = getColors();

    sprintf(scorePlayer, "Score: %d", score.score);

    al_draw_text(font22, colors.WHITE, (0.5 * SCREEN_W/15), SCREEN_H/20, 0, scorePlayer);
}

void drawGameOver(Score score, ALLEGRO_FONT *font22, ALLEGRO_FONT *font26){
    Colors colors = getColors();
    char titleGameOver[10];
    char titleStatistics[15];
    char scorePlayer[20];
    char record[30];
    char bydoMinion1Statistics[60];
    char bydoMinion2Statistics[60];
    char bydoMinion3Statistics[60];
    
    al_clear_to_color(colors.BLACK);

    sprintf(titleGameOver, "Game over");
    sprintf(scorePlayer, "Score: %d", score.score);
    sprintf(record, score.newRecord ? "New record: %d !!" : "Current record: %d", score.record);
    sprintf(titleStatistics, "Statistics:");
    sprintf(bydoMinion1Statistics, "%d Gouache were destroyed", score.numerKilledBydoMinion1);
    sprintf(bydoMinion2Statistics, "%d Fenrir were destroyed", score.numerKilledBydoMinion2);
    sprintf(bydoMinion3Statistics, "%d Ollie were destroyed", score.numerKilledBydoMinion3);

    al_draw_text(font26, colors.CYAN, (SCREEN_W/2 - al_get_text_width(font26, titleGameOver)/2), SCREEN_H/12, 0, titleGameOver);
    al_draw_text(font22, score.newRecord ? colors.GREEN : colors.RED, (SCREEN_W/2 - al_get_text_width(font22, scorePlayer)/2), SCREEN_H/5, 0, scorePlayer);
    al_draw_text(font22, colors.GREEN, (SCREEN_W/2 - al_get_text_width(font22, record)/2), 1.35*SCREEN_H/5, 0, record);
    al_draw_text(font26, colors.CYAN, (SCREEN_W/2 - al_get_text_width(font26, titleStatistics)/2), 1.2*SCREEN_H/3, 0, titleStatistics);
    al_draw_text(font22, colors.ORANGE, (SCREEN_W/2 - al_get_text_width(font22, bydoMinion1Statistics)/2), SCREEN_H/2, 0, bydoMinion1Statistics);
    al_draw_text(font22, colors.ORANGE, (SCREEN_W/2 - al_get_text_width(font22, bydoMinion2Statistics)/2), 1.15*SCREEN_H/2, 0, bydoMinion2Statistics);
    al_draw_text(font22, colors.ORANGE, (SCREEN_W/2 - al_get_text_width(font22, bydoMinion3Statistics)/2), 1.3*SCREEN_H/2, 0, bydoMinion3Statistics);
}

