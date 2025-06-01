// CharlesStoeterGameDesignAssignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

//global x and global y for mouse clicks
int mx = 0;
int my = 0;

int main()
{

	//Constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;
	const int BOARD_SIZE = 5; // 5x5 board
	const int CELL_SIZE = SCREEN_WIDTH / BOARD_SIZE; // Size of each cell in the board

	// Initialize Allegro
	if (!al_init()) {
		std::cerr << "Failed to initialize Allegro!" << std::endl;
		return -1;
	}
	if (!al_init_font_addon()) {
		std::cerr << "Failed to initialize font addon!" << std::endl;
		return -1;
	}
	if (!al_init_ttf_addon()) {
		std::cerr << "Failed to initialize TTF addon!" << std::endl;
		return -1;
	}
	if (!al_init_primitives_addon()) {
		std::cerr << "Failed to initialize primitives addon!" << std::endl;
		return -1;
	}

	al_install_mouse();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		std::cerr << "Failed to create display!" << std::endl;
		return -1;
	}

	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 24, 0);
	if (!font) {
		std::cerr << "Failed to load font!" << std::endl;
		al_destroy_display(display);
		return -1;
	}

	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // 60 FPS timer

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	bool runninng = true;
	bool redraw = true;









	// Your game logic here
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_uninstall_system();
	return 0;

}

