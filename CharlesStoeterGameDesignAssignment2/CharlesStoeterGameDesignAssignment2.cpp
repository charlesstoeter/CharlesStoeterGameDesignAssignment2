// CharlesStoeterGameDesignAssignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

//global x and global y for mouse clicks

int main()
{
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







	// Your game logic here
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_uninstall_system();
	return 0;

}

