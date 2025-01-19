#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <fstream>
#include "moving_characters.h"
#include "map_func.h"

void insert_to_q(queue<Text>& q, const Text& text1, const Text& text2, const Text& text3, const Text& text4, const Text& text5)
{
	q.push(text1);
	q.push(text2);
	q.push(text3);
	q.push(text4);
	q.push(text5);
}

void generate_pause_text(Font& font, Text& paused_text, Text& continue_text, Text& help_text, Text& quit_text, Text& confirmation) {
	if (!font.loadFromFile("bruno.ttf")) {
		cerr << "Failed to load font!" << endl;
		exit(-1);
	}
	queue<Text> texts;
	insert_to_q(texts, paused_text, continue_text, help_text, quit_text, confirmation);


	texts.front().setFont(font);
	texts.front().setString("Game Paused");
	texts.front().setCharacterSize(60);
	texts.front().setFillColor(Color::White);
	texts.front().setPosition(WIDTH / 2 - texts.front().getGlobalBounds().width / 2, 50);
	paused_text = texts.front();
	texts.pop();

	texts.front().setFont(font);
	texts.front().setString("Press F1 to continue");
	texts.front().setCharacterSize(30);
	texts.front().setFillColor(Color::White);
	texts.front().setPosition(WIDTH / 2 - texts.front().getGlobalBounds().width / 2, 500);
	continue_text = texts.front();
	texts.pop();

	texts.front().setFont(font);
	texts.front().setString("\254Press F1 for help\n\254Use arrows to move\n\254Press escape to quit the game\n\nCollect the Points and avoid the Ghosts!");
	texts.front().setCharacterSize(30);
	texts.front().setFillColor(Color::White);
	texts.front().setPosition(WIDTH / 2 - texts.front().getGlobalBounds().width / 2, 200);
	help_text = texts.front();
	texts.pop();

	texts.front().setFont(font);
	texts.front().setString("Are you sure you want to quit?");
	texts.front().setCharacterSize(60);
	texts.front().setFillColor(Color::White);
	texts.front().setPosition(WIDTH / 2 - texts.front().getGlobalBounds().width / 2, 50);
	quit_text = texts.front();
	texts.pop();

	texts.front().setFont(font);
	texts.front().setString("Press Y to quit or N to continue");
	texts.front().setCharacterSize(30);
	texts.front().setFillColor(Color::White);
	texts.front().setPosition(WIDTH / 2 - texts.front().getGlobalBounds().width / 2, 500);
	confirmation = texts.front();
	texts.pop();

}

void choose_map(RenderWindow& window, Font& font, int& choice, Sprite& background_sprite, RectangleShape& dark_background, Text& title, Text& author, string& player_name) {
	Text map_text, name_text, prompt_text;
	map_text.setFont(font);
	map_text.setString("1.  Map 1\n2. Map 2\n3. Map 3");
	map_text.setCharacterSize(30);
	map_text.setFillColor(Color::White);
	map_text.setPosition(WIDTH / 2 - map_text.getGlobalBounds().width / 2, 300);

	prompt_text.setFont(font);
	prompt_text.setString("Enter your name: ");
	prompt_text.setCharacterSize(30);
	prompt_text.setFillColor(Color::White);
	prompt_text.setPosition(WIDTH / 2 - prompt_text.getGlobalBounds().width / 2, 200);

	name_text.setFont(font);
	name_text.setCharacterSize(30);
	name_text.setFillColor(Color::White);
	name_text.setPosition(WIDTH / 2 - name_text.getGlobalBounds().width / 2 - 100, 250);

	bool name_entered = false;
	player_name = "";

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered && !name_entered) {
				if (event.text.unicode == '\b' && !player_name.empty()) {
					player_name.pop_back();
				}
				else if (event.text.unicode < 128 && event.text.unicode != '\b') {
					player_name += static_cast<char>(event.text.unicode);
				}
				name_text.setString(player_name);
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && !name_entered) {
				name_entered = true;
			}
			if (name_entered) {
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num1) {
					choice = 1;
					return;
				}
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num2) {
					choice = 2;
					return;
				}
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num3) {
					choice = 3;
					return;
				}
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
					window.close(); // Quit the game
			}
		}

		window.clear();
		window.draw(background_sprite);
		window.draw(dark_background);
		window.draw(title);
		if (!name_entered) {
			window.draw(prompt_text);
			window.draw(name_text);
		}
		else {
			window.draw(map_text);
		}
		window.draw(author);
		window.display();
	}
}

void display_menu(RenderWindow& window, Font& font, int& choice, string& player_name) {
	Texture background_texture;
	if (!background_texture.loadFromFile("back1.png")) {
		cerr << "Failed to load background image!" << endl;
		exit(-1);
	}
	Sprite background_sprite;
	background_sprite.setTexture(background_texture);
	RectangleShape dark_background(Vector2f(WIDTH, HEIGHT));
	dark_background.setFillColor(Color(0, 0, 0, 200));
	Text title, start_text, quit_text, author;
	title.setFont(font);
	title.setString("PacMan");
	title.setCharacterSize(60);
	title.setFillColor(Color::White);
	title.setPosition(WIDTH / 2 - title.getGlobalBounds().width / 2, 100);

	start_text.setFont(font);
	start_text.setString("Press Enter to Start");
	start_text.setCharacterSize(30);
	start_text.setFillColor(Color::White);
	start_text.setPosition(WIDTH / 2 - start_text.getGlobalBounds().width / 2, 300);

	quit_text.setFont(font);
	quit_text.setString("Press Escape to Quit");
	quit_text.setCharacterSize(30);
	quit_text.setFillColor(Color::White);
	quit_text.setPosition(WIDTH / 2 - quit_text.getGlobalBounds().width / 2, 400);

	author.setFont(font);
	author.setString("Nikodem Kozlowski 199239 ARiSS1\n	Tomasz Nazar 197613 ACiR3");
	author.setCharacterSize(15);
	author.setFillColor(Color::White);
	author.setPosition(WIDTH / 2 - author.getGlobalBounds().width / 2, 600);


	ConvexShape animated_shape;
	animated_shape.setPointCount(5); // Przykład nieregularnego kształtu
	animated_shape.setPoint(0, Vector2f(0, 0));
	animated_shape.setPoint(1, Vector2f(40, 10));
	animated_shape.setPoint(2, Vector2f(30, 40));
	animated_shape.setPoint(3, Vector2f(10, 50));
	animated_shape.setPoint(4, Vector2f(0, 30));
	animated_shape.setFillColor(Color::Red);
	animated_shape.setPosition(WIDTH - 100, HEIGHT - 100); // Pozycja w prawym dolnym rogu

	float rotation_angle = 0.05f; // Prędkość obrotu
	float move_delta = 0.05f;     // Prędkość ruchu
	float direction = 0.1f;      // Kierunek ruchu (1 - w górę, -1 - w dół)

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
				choose_map(window, font, choice, background_sprite, dark_background, title, author, player_name);
				return;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close(); // Quit the game
		}

		animated_shape.rotate(rotation_angle);
		Vector2f current_position = animated_shape.getPosition();
		if (current_position.y <= HEIGHT - 120 || current_position.y >= HEIGHT - 80) {
			direction = -direction; // Odwróć kierunek ruchu
		}

		animated_shape.move(0, direction * move_delta);
		window.clear();
		window.draw(background_sprite);
		window.draw(dark_background);
		window.draw(title);
		window.draw(start_text);
		window.draw(quit_text);
		window.draw(author);
		window.draw(animated_shape);
		window.display();
	}
}

void display_game_over(RenderWindow& window, Font& font, int score) {
	Text game_over_text, return_to_menu_text, score_text;
	game_over_text.setFont(font);
	game_over_text.setString("Game Over");
	game_over_text.setCharacterSize(60);
	game_over_text.setFillColor(Color::Red);
	game_over_text.setPosition(WIDTH / 2 - game_over_text.getGlobalBounds().width / 2, 200);

	return_to_menu_text.setFont(font);
	return_to_menu_text.setString("Press Escape to return to menu");
	return_to_menu_text.setCharacterSize(30);
	return_to_menu_text.setFillColor(Color::White);
	return_to_menu_text.setPosition(WIDTH / 2 - return_to_menu_text.getGlobalBounds().width / 2, 400);

	score_text.setFont(font);
	score_text.setString("Score: " + to_string(score));
	score_text.setCharacterSize(40);
	score_text.setFillColor(Color::Yellow);
	score_text.setPosition(WIDTH / 2 - score_text.getGlobalBounds().width / 2, 300);

	RectangleShape dark_background(Vector2f(WIDTH, HEIGHT));
	dark_background.setFillColor(Color(0, 0, 0, 200)); // Semi-transparent background

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				return; // Exit the "Game Over" screen
		}

		window.clear();
		window.draw(dark_background);
		window.draw(game_over_text);
		window.draw(score_text);
		window.draw(return_to_menu_text);
		window.display();
	}
}

void reset_game_state(punkty& punkty, labirynth& labirynth, int& score) {
	punkty.clear(); // Wyczyszczenie punktów
	labirynth.clear_walls(); // Wyczyszczenie ścian labiryntu
	score = 0; // Zresetowanie wyniku
}

Texture load_texture(const string& filename) {
	Texture texture;
	if (!texture.loadFromFile(filename)) {
		cerr << "Failed to load texture: " << filename << endl;
		exit(-1);
	}
	return texture;
}

void draw_high_scores(RenderWindow& window, Font& font) {
	ifstream file("highscores.txt");
	if (!file.is_open()) {
		cerr << "Failed to open highscores file!" << endl;
		return;
	}

	vector<pair<string, int>> scores;
	string name;
	int score;
	while (file >> name >> score) {
		scores.push_back(make_pair(name, score));
	}
	file.close();

	sort(scores.begin(), scores.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
		return b.second < a.second;
		});

	Text title, score_text, cont;
	title.setFont(font);
	title.setString("High Scores");
	title.setCharacterSize(60);
	title.setFillColor(Color::White);
	title.setPosition(WIDTH / 2 - title.getGlobalBounds().width / 2, 50);

	window.clear();
	window.draw(title);

	int y_offset = 150;
	int i = 0;
	for (const auto& entry : scores) {
		i++;
		score_text.setFont(font);
		score_text.setString(entry.first + ": " + to_string(entry.second));
		score_text.setCharacterSize(25);
		score_text.setFillColor(Color::White);
		score_text.setPosition(WIDTH / 2 - score_text.getGlobalBounds().width / 2, y_offset);
		window.draw(score_text);
		y_offset += 40;
		if (i == 12)
			break;
	}
	cont.setFont(font);
	cont.setString("Press Enter to continue");
	cont.setCharacterSize(30);
	cont.setFillColor(Color::White);
	cont.setPosition(WIDTH / 2 - cont.getGlobalBounds().width / 2, 650);
	window.draw(cont);

	window.display();
	Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
				return;
		}
		sleep(milliseconds(1));
	}
}

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