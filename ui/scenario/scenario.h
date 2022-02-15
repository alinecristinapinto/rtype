#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "../../interfaces/scenario_interface.h"

void initStars(Star stars[], int screen_w, int screen_h, float moveSpeed);

void updateStars(Star stars[], int screen_w);

void drawStars(Star stars[]);

void initScore(Score *score);

void updateScore(Score *score);

void drawScore(Score score, int screen_w, int screen_h, ALLEGRO_FONT *font);

void drawGameOver(Score score, int screen_w, int screen_h, ALLEGRO_FONT *font22, ALLEGRO_FONT *font26);
