#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include <queue>
#include "moving_characters.h"

using namespace std;
using namespace sf;

void map1(labirynth& l, punkty& punkty);
void map2(labirynth& l, punkty& punkty);
void map3(labirynth& l, punkty& punkty);

void fill_with_punkty(punkty& punkty, const float x, const float y, const int k, const int w, const float distance) {
	for (int i = 0; i < k; i++) {
		punkty.add_punkt(x + i * distance, y);
		for (int j = 0; j < w; j++)
			punkty.add_punkt(x + i * distance, y + j * distance);
	}
}

queue<Text> insert_to_q(queue<Text>& q, const Text& text1, const Text& text2, const Text& text3, const Text& text4, const Text& text5)
{
	q.push(text1);
	q.push(text2);
	q.push(text3);
	q.push(text4);
	q.push(text5);
	return q;
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
	texts.empty();

}

void choose_map(RenderWindow& window, Font& font, int& choice, Sprite& background_sprite, RectangleShape& dark_background, Text& title, Text& author) {
	Text map_text;
	map_text.setFont(font);
	map_text.setString("1.  Map 1\n2. Map 2\n3. Map 3");
	map_text.setCharacterSize(30);
	map_text.setFillColor(Color::White);
	map_text.setPosition(WIDTH / 2 - map_text.getGlobalBounds().width / 2, 300);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
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

		window.clear();
		window.draw(background_sprite);
		window.draw(dark_background);
		window.draw(title);
		window.draw(map_text);
		window.draw(author);
		window.display();
	}
}

void display_menu(RenderWindow& window, Font& font, int& choice) {
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
				choose_map(window, font, choice, background_sprite, dark_background, title, author);
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

		animated_shape.move( 0 ,direction * move_delta);
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

	//score text
	score_text.setFont(font);
	score_text.setCharacterSize(30);
	score_text.setFillColor(Color::White);
	score_text.setPosition(10, 10);

	RectangleShape dark_background(Vector2f(WIDTH, HEIGHT));
	dark_background.setFillColor(Color(0, 0, 0, 220)); // Semi-transparent dark background
	int choice = 0;
	// Display the menu
	display_menu(window, font, choice);

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
				quit_confirmation = true;
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

				display_game_over(window, font, score);
				display_menu(window, font, choice);
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

			// Example of changing the texture dynamically
			/*if (score == 4) {
				Texture new_texture = load_texture("pacman_left/0.png");
				p.setTexture(new_texture);
			}*/
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
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::N))
				quit_confirmation = false;
		}
		window.display();
	}
	return 0;
}

void map1(labirynth& l, punkty& punkty)

{
	fill_with_punkty(punkty, 50, 50, 24, 13, 50);

	//ramki
	l.add_wall(0, 0, 1270, 20); // sciana pozioma gorna
	l.add_wall(0, 20, 20, 680); // sciana pionowa lewa
	l.add_wall(0, 700, 1270, 20); // sciana pozioma dolna
	l.add_wall(1250, 20, 20, 680); // sciana pionowa prawa
	//4 rogi
	//lewy gora
	l.add_wall(100, 100, 20, 220); //pionowa
	l.add_wall(120, 100, 100, 20); //pozioma
	//lewy dol
	l.add_wall(100, 400, 20, 220);//pionowa
	l.add_wall(120, 600, 100, 20);//pozioma
	//prawy gora
	l.add_wall(1150, 100, 20, 220);//pionowa
	l.add_wall(1050, 100, 100, 20);//pozioma

	//prawy dol
	l.add_wall(1150, 400, 20, 220); //pionowa
	l.add_wall(1050, 600, 100, 20); //pozioma


	//4 bolce pionowe
	l.add_wall(300, 20, 20, 100); //lewy gora
	l.add_wall(950, 20, 20, 100); //prawy gora
	l.add_wall(300, 600, 20, 100); //lewy dol
	l.add_wall(950, 600, 20, 100); //prawy dol

	//6 bolce poziome
	l.add_wall(200, 200, 120, 70); //lewy gorny
	l.add_wall(200, 350, 200, 20); //lewy srodek
	l.add_wall(200, 450, 120, 70); //lewy dol
	l.add_wall(950, 200, 120, 70); //prawy gora
	l.add_wall(870, 350, 200, 20); //prawy srodek
	l.add_wall(950, 450, 120, 70); //prawy dol

	//2 dlugie pionowe
	l.add_wall(400, 200, 20, 320);//lewy
	l.add_wall(850, 200, 20, 320);//prawy

	//2 dlugie poziome
	l.add_wall(400, 100, 470, 20);//gorny
	l.add_wall(400, 600, 470, 20);//dolny

	//srodek
	l.add_wall(500, 120, 20, 200);//pionowy gorny
	l.add_wall(500, 400, 20, 200);//pionowy dolny
	l.add_wall(750, 120, 20, 200);
	l.add_wall(750, 400, 20, 200);
	l.add_wall(600, 350, 70, 20);
	l.add_wall(600, 200, 70, 70);
	l.add_wall(600, 450, 70, 70);

}

void map2(labirynth& l, punkty& punkty)
{
	fill_with_punkty(punkty, 50, 50, 11, 13, 50);
	fill_with_punkty(punkty, 690, 50, 11, 13, 50);
	fill_with_punkty(punkty, 620, 150, 1, 2, 150);
	fill_with_punkty(punkty, 620, 400, 1, 2, 150);

	//ramki

	l.add_wall(0, 0, 1270, 20); // sciana pozioma gorna
	l.add_wall(0, 20, 20, 680); // sciana pionowa lewa
	l.add_wall(0, 700, 1270, 20); // sciana pozioma dolna
	l.add_wall(1240, 20, 30, 680); // sciana pionowa prawa
	///lewa strona
	l.add_wall(100, 600, 120, 20);//poziomy
	l.add_wall(100, 500, 20, 120);//pionowy

	l.add_wall(300, 600, 20, 100);//pionowy

	l.add_wall(400, 600, 100, 20);//poziomy
	l.add_wall(500, 500, 20, 120);//pionowy
	l.add_wall(400, 500, 20, 20);//kwadrat

	l.add_wall(200, 500, 120, 20);//poziomy cienki
	l.add_wall(200, 400, 20, 100);//pionowy 
	l.add_wall(100, 400, 100, 20);//poziomy gruby

	l.add_wall(300, 400, 120, 20);//poziomy lewy
	l.add_wall(300, 200, 20, 200);//pionowy lewy
	l.add_wall(500, 200, 20, 220);//pionowy prawy
	l.add_wall(400, 300, 100, 20);//poziomy prawy
	l.add_wall(400, 200, 20, 20);//kwadrat

	l.add_wall(20, 300, 200, 20);//gruby poziomy
	l.add_wall(200, 200, 20, 100);//pionowy dolny

	l.add_wall(100, 100, 20, 120);//pionowy gorny

	l.add_wall(120, 100, 100, 20);//poziomy gorny

	l.add_wall(300, 20, 20, 100);//pionowy samotnik
	l.add_wall(400, 100, 120, 20);//poziomy samotnik

	//srodek
	l.add_wall(600, 20, 60, 100);//gorny prostokat
	l.add_wall(600, 200, 60, 70);//gorny kwadrat 
	l.add_wall(600, 350, 60, 20);//srodkowy 
	l.add_wall(600, 450, 60, 70);//dolny kwadrat
	l.add_wall(600, 600, 60, 100);//dolny prostokat


	//prawa strona
	l.add_wall(740, 100, 120, 20);//poziomy lewy
	l.add_wall(740, 120, 20, 100);//pionowy lewy
	l.add_wall(840, 200, 20, 20);//kwadrat

	l.add_wall(940, 20, 20, 100);//pionowy samotny
	l.add_wall(1040, 100, 120, 20);//poziomy rog
	l.add_wall(1140, 110, 20, 110);//pionowy rog

	l.add_wall(940, 200, 120, 20);//poziomy
	l.add_wall(1040, 220, 20, 100);//pionowy cienki
	l.add_wall(1060, 300, 100, 20);//poziomy gruby

	l.add_wall(740, 300, 20, 220);//pionowy
	l.add_wall(760, 400, 100, 20);//poziomy
	l.add_wall(840, 300, 120, 20);//pionowy
	l.add_wall(940, 320, 20, 200);//poziomy
	l.add_wall(840, 500, 20, 20);//kwadrat

	l.add_wall(1040, 400, 200, 20);//gruby ze sciany
	l.add_wall(1040, 410, 20, 110);//pionowy

	l.add_wall(740, 600, 120, 20);//poziomy samotnik
	l.add_wall(940, 600, 20, 100);//pionowy samotnik
	l.add_wall(1040, 600, 120, 20);//poziomy
	l.add_wall(1140, 500, 20, 120);
}

void map3(labirynth& l, punkty& punkty)
{
	fill_with_punkty(punkty, 50, 50, 24, 13, 50);
	//ramki
	l.add_wall(0, 0, 1270, 20); // sciana pozioma gorna
	l.add_wall(0, 20, 20, 680); // sciana pionowa lewa
	l.add_wall(0, 700, 1270, 20); // sciana pozioma dolna
	l.add_wall(1250, 20, 20, 680); // sciana pionowa prawa

	//lewy rog
	l.add_wall(20, 500, 100, 20);//maly bolec ze sciany poziomy
	l.add_wall(300, 400, 70, 20);//samotny poziomy

	//niepelnosprawne f
	l.add_wall(100, 600, 270, 20);//poziomy z f
	l.add_wall(300, 500, 20, 100);//pionowy z f

	//odwrocona elka
	l.add_wall(200, 400, 20, 120);//pionowy z odwroconej elki
	l.add_wall(90, 400, 110, 20);//poziomy z odwroconej elki

	//kinole
	l.add_wall(400, 500, 120, 20);//kinol dolny poziome
	l.add_wall(450, 520, 20, 100);//kinol dolny pionowe

	l.add_wall(450, 320, 20, 100);//kinol pionowe gorne
	l.add_wall(400, 300, 120, 20);//kinol poziome gora

	l.add_wall(400, 100, 120, 20);//kinol najwyzszy poziome
	l.add_wall(450, 120, 20, 100);//kinol najwyzszy pionowe

	//prawy rog
	l.add_wall(900, 600, 120, 20); // poziomy dol 1
	l.add_wall(1100, 600, 70, 20);//poziomy dol 2
	l.add_wall(800, 500, 370, 20);//poziomy gora
	l.add_wall(900, 400, 20, 100);//pionowy gora
	l.add_wall(550, 400, 70, 20);
	l.add_wall(1000, 400, 170, 20);
	//niepelnosprawne f
	l.add_wall(550, 600, 270, 20);//poziomy z f
	l.add_wall(600, 500, 20, 100);//pionowy z f



	//odwr elka
	l.add_wall(700, 400, 20, 120);//pionowy z elki
	l.add_wall(720, 400, 100, 20);//poziomy z elki

	//srodek
	l.add_wall(300, 220, 20, 100);//pionowy lewy
	l.add_wall(300, 200, 70, 20);//poziomy lewy
	l.add_wall(600, 220, 20, 100);//pionowy prawy
	l.add_wall(550, 200, 70, 20);//poziomy prawy


	//lewy gora
	l.add_wall(100, 100, 20, 220);//pionowy
	l.add_wall(120, 200, 100, 20);//poziomy
	l.add_wall(200, 20, 20, 80);//pionowy lewy gora
	l.add_wall(200, 100, 120, 20);//poziomy lewy gora
	l.add_wall(200, 300, 20, 20);//kwadrat

	//prawy gora
	l.add_wall(600, 100, 120, 20);//poziomy prawy gora
	l.add_wall(700, 20, 20, 80);//pionowy prawy gora
	l.add_wall(700, 200, 100, 20);//poziomy
	l.add_wall(800, 100, 20, 220);//pionowy
	l.add_wall(700, 300, 20, 20);//kwadrat
	//kwadrat duzy
	l.add_wall(900, 100, 20, 220);//lewy bok
	l.add_wall(920, 100, 250, 20);//gora
	l.add_wall(1150, 100, 20, 220);//prawy bok
	l.add_wall(900, 300, 70, 20);//lewy dol
	l.add_wall(1050, 300, 100, 20);//prawy dol
	l.add_wall(1000, 200, 70, 20);//kwadrat w srodku
}
