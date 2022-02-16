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

void getGameHistory(Score *score);
void updateGameHistory(Score score);
void endGame(Score score, ALLEGRO_FONT *font22, ALLEGRO_FONT *font26);

int main(int argc, char **argv){
	srand(time(NULL));
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//----------------------- starting routines ---------------------------------------
	
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}
   
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   
	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());	

	al_start_timer(timer);

	//----------------------- elements -----------------------
	Colors colors = getColors();

	Star stars_p1[NUM_STARS];
	initStars(stars_p1, 3);
	Star stars_p2[NUM_STARS];
	initStars(stars_p2, 5);

	Spaceship spaceship;
	initSpaceship(&spaceship);
	
	Projectile projectile;
	initProjectile(&projectile, spaceship);

	Block block;
	initBlock(&block);

	Enemy enemies[NUM_ENEMIES];
	ALLEGRO_BITMAP *enemiesImage = al_load_bitmap("assets/img/enemies.png");
	initEnemies(enemies, enemiesImage);

	Score score;
	initScore(&score);
	getGameHistory(&score);
    ALLEGRO_FONT *font22 = al_load_font("assets/fonts/AtariSmall.ttf", 22, 1);
	ALLEGRO_FONT *font26 = al_load_font("assets/fonts/AtariSmall.ttf", 26, 1);
	
	//----------------------- main -----------------------

	int playing = 1;
	while(playing) {
		ALLEGRO_EVENT ev;
		
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
			endGame(score, font22, font26);
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
			handleCollisionBetweenProjetileAndBlock(&projectile, spaceship, block);
			handleCollisionBetweenProjectileAndEnemies(&projectile, spaceship, &score, enemies);
			updateScore(&score);

			releaseEnemies(enemies);
			updateEnemies(enemies);
			drawEnemies(enemies);
			handleCollisionBetweenEnemies(enemies);
			handleCollisionBetweenEnemiesAndBlock(enemies, block);

			drawScore(score, font22);
			
			int gameOver = spaceshipAndEnemiesCollision(spaceship, enemies) ||
					  spaceshipAndBlockCollision(spaceship, block);

			if(gameOver){
				playing = 0;
				endGame(score, font22, font26);
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
	al_destroy_bitmap(spaceship.image);
	al_destroy_bitmap(block.image);
	al_destroy_bitmap(enemiesImage);
	al_destroy_font(font22);
	al_destroy_font(font26);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
 
	return 0;
}

void getGameHistory(Score *score){
	FILE *scoreFile = openFile(scoreFileName, "r");
	if(scoreFile){
		readGameHistory(scoreFile, score);
	}
	fclose(scoreFile);
}

void updateGameHistory(Score score){
	if(score.score >= score.record){
		FILE *scoreFile = openFile(scoreFileName, "w+");
		writeGameHistory(scoreFile, score);
		closeFile(scoreFile);
	}
}

void endGame(Score score, ALLEGRO_FONT *font22, ALLEGRO_FONT *font26){
	updateGameHistory(score);
	drawGameOver(score, font22, font26);
    al_flip_display();
    al_rest(3);
}
