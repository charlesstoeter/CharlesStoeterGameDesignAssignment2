// CharlesStoeterGameDesignAssignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "GameBoard.h"
#include <direct.h>
#include <fstream>
#include <sstream>

//global x and global y for mouse clicks
int mx = 0;
int my = 0;


// Enum for different shapes
void drawShape(Shape shape, float cx, float cy, float size);


int main()
{


	//Constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;
	const int GRID_SIZE = 5; // 5x5 board
	const int CELL_SIZE = SCREEN_WIDTH / GRID_SIZE; // Size of each cell in the board



	

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


	ALLEGRO_FONT* font = al_load_ttf_font("ARIAL.TTF", 24, 0);
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

	bool running = true;
	bool redraw = true;


	//variables to track the first and second  cells
	int firstRow = -1, firstCol = -1;
	int secondRow = -1, secondCol = -1;
	bool checkingMatch = false;



	GameBoard board;

	while (running) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = false;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			mx = ev.mouse.x;
			my = ev.mouse.y;

			int row = my / CELL_SIZE;
			int col = mx / CELL_SIZE;

			// Skip invalid or duplicate clicks
			if (row >= GRID_SIZE || col >= GRID_SIZE) continue;
			if (board.isRevealed(row, col)) continue;
			if (row == firstRow && col == firstCol) continue;

			// Process click
			if (firstRow == -1 && firstCol == -1) {
				firstRow = row;
				firstCol = col;
				board.reveal(row, col);
			}
			else if (secondRow == -1 && secondCol == -1) {
				secondRow = row;
				secondCol = col;
				board.reveal(row, col);
				checkingMatch = true;
			}

			redraw = true;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			for (int i = 0; i < GRID_SIZE; ++i) {
				for (int j = 0; j < GRID_SIZE; ++j) {
					int cx = j * CELL_SIZE + CELL_SIZE / 2;
					int cy = i * CELL_SIZE + CELL_SIZE / 2;

					// draw border
					al_draw_rectangle(j * CELL_SIZE, i * CELL_SIZE,
						(j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE,
						al_map_rgb(255, 255, 255), 2);

					if (board.isRevealed(i, j)) {
						Shape shape = board.getShapeAt(i, j);
						if (shape != EMPTY) {
							drawShape(shape, cx, cy, CELL_SIZE * 0.6f);
						}
					}
				}
			}
			al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, "Memory Game");

			int matched = board.getMatchedPairs();
			int remaining = board.getRemainingPairs();

			std::string status = "Matched: " + std::to_string(matched) + "\nLeft: " + std::to_string(remaining);

			al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH - 200, SCREEN_HEIGHT - 60, 0, status.c_str());


			al_flip_display();


			if (checkingMatch) {
				Shape shape1 = board.getShapeAt(firstRow, firstCol);
				Shape shape2 = board.getShapeAt(secondRow, secondCol);

				if (board.compare(firstRow, firstCol, secondRow, secondCol)) {
					board.incrementMatchCount();
					std::cout << "Match.\n";
					// keep both revealed
				}
				else {
					std::cout << "No match.\n";

					al_rest(5.0); 


					board.hide(firstRow, firstCol);
					board.hide(secondRow, secondCol);
				}

				if (board.allMatched()) {
					std::cout << "All pairs matched. Resetting game.\n";
					al_rest(2.0); // short pause
					board.resetGame();
				}

				

				// Reset guesses
				firstRow = -1;
				firstCol = -1;
				secondRow = -1;
				secondCol = -1;
				checkingMatch = false;
				redraw = true; // trigger redraw
			}
		}
	}




	// Your game logic here
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;

}

void drawShape(Shape shape, float cx, float cy, float size) {
	if (shape == CIRCLE) {
		al_draw_filled_circle(cx, cy, size / 2, al_map_rgb(255, 0, 0));
	}

	else if (shape == RECTANGLE) {
		al_draw_filled_rectangle(cx - size / 2, cy - size / 2,
			cx + size / 2, cy + size / 2,
			al_map_rgb(0, 255, 0));
	}

	else if (shape == OVAL) {
		al_draw_filled_ellipse(cx, cy, size / 2, size / 3, al_map_rgb(0, 0, 255));
	}

	else if (shape == TRIANGLE) {
		al_draw_filled_triangle(cx, cy - size / 2,
			cx - size / 2, cy + size / 2,
			cx + size / 2, cy + size / 2,
			al_map_rgb(255, 255, 0));
	}

	else if (shape == DIAMOND) {
		float points[] = {
			cx, cy - size / 2,
			cx - size / 2, cy,
			cx, cy + size / 2,
			cx + size / 2, cy
		};
		al_draw_filled_polygon(points, 4, al_map_rgb(255, 0, 255));
	}

	else if (shape == OCTAGON) {
		al_draw_filled_rectangle(cx - size / 3, cy - size / 3, cx + size / 3, cy + size / 3, al_map_rgb(255, 255, 255));
	}
	else {
		std::cout << "Unknown shape ID: " << shape << std::endl;
	}
}

