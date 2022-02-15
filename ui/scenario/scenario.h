#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "../../interfaces/scenario_interface.h"

void initStars(Star stars[], float moveSpeed);

void updateStars(Star stars[]);

void drawStars(Star stars[]);

void initScore(Score *score);

void updateScore(Score *score);

void drawScore(Score score, ALLEGRO_FONT *font22);

void drawGameOver(Score score, ALLEGRO_FONT *font22, ALLEGRO_FONT *font26);
