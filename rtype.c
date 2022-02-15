#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "styles/colors.h"
#include "ui/spaceship/spaceship.h"
#include "ui/scenario/scenario.h"
#include "ui/obstacles/block.h"
#include "ui/obstacles/enemies.h"
#include "utils/utils.h"
#include "utils/constants.h"

char scoreFileName [20] = "scores.dat";

void getGameHistory(Score *score){
	FILE *scoreFile = openFile(scoreFileName, "r");
	if(scoreFile){
		readGameHistory(scoreFile, score);
	}
	fclose(scoreFile);
}

void updateGameHistory(Score score){
    FILE *scoreFile = openFile(scoreFileName, "w+");
    writeGameHistory(scoreFile, score);
    closeFile(scoreFile);
}

int main(int argc, char **argv){
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//----------------------- starting routines ---------------------------------------
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
    timer = al_create_timer(1.0 / FPS);
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) al_destroy_timer(timer);
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	event_queue = al_create_event_queue();
	if(!event_queue) al_destroy_display(display);
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

	//----------------------- elements -----------------------
	Colors colors = getColors();

	srand(time(NULL));

	Star stars_p1[NUM_STARS];
	initStars(stars_p1, 3);
	Star stars_p2[NUM_STARS];
	initStars(stars_p2, 5);

	Spaceship spaceship;
	ALLEGRO_BITMAP *spaceshipImage = al_load_bitmap("assets/img/spaceship.png");
	spaceship.image = spaceshipImage;
	initSpaceship(&spaceship);
	
	Projectile projectile;
	initProjectile(&projectile, spaceship);

	Block block;
	ALLEGRO_BITMAP *blockImage = al_load_bitmap("assets/img/block.png");
	block.image = blockImage;
	initBlock(&block);

	Enemy enemies[NUM_ENEMIES];
	ALLEGRO_BITMAP *enemiesImage = al_load_bitmap("assets/img/enemies.png");
	initEnemies(enemies, enemiesImage);

	Score score;
	initScore(&score);
	getGameHistory(&score);
    ALLEGRO_FONT *font = al_load_font("assets/fonts/AtariSmall.ttf", 22, 1);
	ALLEGRO_FONT *font32 = al_load_font("assets/fonts/AtariSmall.ttf", 26, 1);
	
	//----------------------- main -----------------------

	int playing = 1;
	while(playing) {
		ALLEGRO_EVENT ev;
		
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		} else if(ev.type == ALLEGRO_EVENT_TIMER) {

			updateStars(stars_p1);
			drawStars(stars_p1);

			updateStars(stars_p2);
			drawStars(stars_p2);

			updateBlock(&block);
			drawBlock(block);

			updateSpaceship(&spaceship);
			drawSpaceship(spaceship);

			updateProjectile(&projectile, spaceship);
			drawProjectile(projectile);
			projectileAndEnemiesCollision(&projectile, spaceship, &score, enemies);
			updateScore(&score);

			releaseEnemies(enemies);
			updateEnemies(enemies);
			drawEnemies(enemies);
			handleCollisionBetweenEnemies(enemies);
			handleCollisionBetweenEnemiesAndBlock(enemies, block);

			drawScore(score, font);
			
			int gameOver = spaceshipAndEnemiesCollision(spaceship, enemies) ||
					  spaceshipAndBlockCollision(spaceship, block);

			if(gameOver){
				playing = 0;
				updateGameHistory(score);
				drawGameOver(score, font, font32);
        		al_flip_display();
        		al_rest(5);
			}

			al_flip_display();
			
		} else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			controlSpaceship(ev.keyboard.keycode, &spaceship, &projectile, KEY_DOWN);
		} else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			controlSpaceship(ev.keyboard.keycode, &spaceship, &projectile, KEY_UP);
		}

		al_clear_to_color(colors.BLACK);
	} 
    
	al_destroy_timer(timer);
	al_destroy_bitmap(spaceshipImage);
	al_destroy_bitmap(blockImage);
	al_destroy_bitmap(enemiesImage);
	al_destroy_font(font);
	al_destroy_font(font32);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
 
	return 0;
}
