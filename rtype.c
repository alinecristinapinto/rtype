#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "styles/colors.h"
#include "ui/spaceship/spaceship.h"
#include "ui/scenario/scenario.h"

const float FPS = 100;  
const int SCREEN_W = 960;
const int SCREEN_H = 540;

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

	Star stars_p1[NUM_STARS];
	initStars(stars_p1, SCREEN_W, SCREEN_H, 3);
	Star stars_p2[NUM_STARS];
	initStars(stars_p2, SCREEN_W, SCREEN_H, 5);

	Spaceship spaceship;
	initSpaceship(&spaceship, SCREEN_H);
	ALLEGRO_BITMAP *spaceshipImage = al_load_bitmap("assets/img/spaceship.png");
	
	Projectile projectile;
	initProjectile(&projectile);
	//----------------------- main -----------------------

	int playing = 1;
	while(playing) {
		ALLEGRO_EVENT ev;
		
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		} else if(ev.type == ALLEGRO_EVENT_TIMER) {

			updateStars(stars_p1, SCREEN_W);
			drawStars(stars_p1);

			updateStars(stars_p2, SCREEN_W);
			drawStars(stars_p2);

			updateSpaceship(&spaceship, SCREEN_W, SCREEN_H);
			drawSpaceship(spaceshipImage, spaceship);

			updateProjectile(&projectile, SCREEN_W);
			drawProjectile(projectile);

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
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
 
	return 0;
}