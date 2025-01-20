#include <SFML/Window.hpp>
#include <cstdlib>
#include "voids.h"
#include "moving_characters.h"
#include "map_func.h"

int main() {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");

	pacman p(550, 645, load_texture("pacman.png"));
	ghost g(40, 40, load_texture("ghost1.png"));
	ghost g1(1180, 40, load_texture("ghost2.png"));
	ghost g2(40, 640, load_texture("ghost1.png"));
	ghost g3(1180, 640, load_texture("ghost2.png"));

	punkty punkty;
	labirynth labirynth;

	bool is_paused = false;
	bool quit_confirmation = false;

	// Load font for displaying "Paused" text
	Font font;
	Text paused_text, continue_text, help_text, quit_text, confirmation, score_text;

	generate_pause_text(font, paused_text, continue_text, help_text, quit_text, confirmation);

	fstream file;
	file.open("highscores.txt", ios::app);
	if (!file.is_open()) {
		cerr << "Failed to open file!" << endl;
		exit(-1);
	}

	//score text
	score_text.setFont(font);
	score_text.setCharacterSize(30);
	score_text.setFillColor(Color::White);
	score_text.setPosition(10, 10);

	RectangleShape dark_background(Vector2f(WIDTH, HEIGHT));
	dark_background.setFillColor(Color(0, 0, 0, 220)); // Semi-transparent dark background
	int choice = 0;
	string player_name;
	// Display the menu
	display_menu(window, font, choice, player_name);

	switch (choice) {
	case 1:
		map1(labirynth, punkty);
		break;
	case 2:
		map2(labirynth, punkty);
		break;
	case 3:
		map3(labirynth, punkty);
		break;
	default:
		window.close();
		return 0;
	}
	int score = 0;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::F1)
				is_paused = !is_paused;
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				quit_confirmation = !quit_confirmation;
		}

		if (!is_paused && !quit_confirmation) {
			// Ruch PacMana
			p.move();
			p.handle_collision_with_wall(labirynth);
			if (punkty.check_collision(p.get_bounding_box())) {
				punkty.remove_punkt(p.get_bounding_box());// Usuwamy punkty, ktore pacman zje
				score++;
			}

			// Ruch duszkow z uwzglednieniem kolizji z labiryntem
			for (const auto& wall : labirynth.get_walls()) {
				if (wall.check_collision(g.get_bounding_box())) g.change_direction();
				if (wall.check_collision(g1.get_bounding_box())) g1.change_direction();
				if (wall.check_collision(g2.get_bounding_box())) g2.change_direction();
				if (wall.check_collision(g3.get_bounding_box())) g3.change_direction();
			}
			g.move_towards_pacman(p, labirynth);  // Duszki uzywaja swojej logiki
			g1.move_towards_pacman(p, labirynth); // Uzycie pustego walla, bo logika jest w glownym
			g2.move_towards_pacman(p, labirynth);
			g3.move_towards_pacman(p, labirynth);

			if (g.check_collision_with_pacman(p) ||
				g1.check_collision_with_pacman(p) ||
				g2.check_collision_with_pacman(p) ||
				g3.check_collision_with_pacman(p))
			{
				cout << "Pac-Man zostal zlapany!\n";

				// Reset pozycji Pac-Mana
				p.p.x = 550;
				p.p.y = 645;

				file << player_name << " " << score;

				display_game_over(window, font, score);
				draw_high_scores(window, font);

				display_menu(window, font, choice, player_name);
				if (choice == 0)
					window.close();

				reset_game_state(punkty, labirynth, score);
				
				// Wczytaj mapę zgodnie z wyborem
				switch (choice) {
				case 1:
					map1(labirynth, punkty);
					break;
				case 2:
					map2(labirynth, punkty);
					break;
				case 3:
					map3(labirynth, punkty);
					break;
				}
				score = 0; // Zresetuj wynik
			}

		}

		// Rysowanie
		window.clear();
		punkty.draw(window);
		score_text.setString("Score: " + to_string(score));
		labirynth.draw(window);
		window.draw(score_text);
		g.draw(window);
		g1.draw(window);
		g2.draw(window);
		g3.draw(window);
		p.draw(window);

		if (is_paused) {
			window.draw(dark_background);
			window.draw(paused_text);
			window.draw(continue_text);
			window.draw(help_text);
		}
		if (quit_confirmation) {
			window.draw(dark_background);
			window.draw(quit_text);
			window.draw(confirmation);
			if (Keyboard::isKeyPressed(Keyboard::Y))
			{
				draw_high_scores(window, font);
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::N))
				quit_confirmation = false;
		}
		window.display();
	}
	file.close();
	return 0;
}