#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <cstdlib>
#include <iostream>

constexpr float SPEED = 0.05;
constexpr int WIDTH = 1270;
constexpr int HEIGHT = 720;
using namespace std;
using namespace sf;

class wall {
public:
	RectangleShape shape;

	wall(const float x, const float y, const float width = 100.f, const float height = 40.f) {
		shape.setSize(Vector2f(width, height));
		shape.setFillColor(Color::Blue);
		shape.setPosition(x, y);
	}
	bool check_collision(const FloatRect& bounding_box) const {
		return shape.getGlobalBounds().intersects(bounding_box);
	}
	void draw(RenderWindow& window) const {
		window.draw(shape);
	}
};

class labirynth {
private:
	std::vector<wall> walls;

public:
	labirynth() {}

	// Dodaje sciane do labiryntu (x,y,width,height)
	void add_wall(float x, float y, float width, float height) {
		walls.emplace_back(x, y, width, height);
	}

	// Sprawdza kolizje z dowolna sciana w labiryncie
	bool check_collision(const FloatRect& bounding_box) const {
		for (const auto& wall : walls) {
			if (wall.check_collision(bounding_box)) {
				return true;
			}
		}
		return false;
	}

	// Rysuje wszystkie sciany w labiryncie
	void draw(RenderWindow& window) const {
		for (const auto& wall : walls) {
			wall.draw(window);
		}
	}

	const std::vector<wall>& get_walls() const {
		return walls;
	}
};

class pacman
{
private:
	struct position
	{
		float x;
		float y;
	};

	float speed;

	struct movement
	{
		bool left;
		bool right;
		bool up;
		bool down;
	};
public:
	position p;
	movement m{};
	pacman()
	{
		p.x = 40;
		p.y = 40;
		speed = SPEED;
	}
	void move()
	{
		if (GetAsyncKeyState(VK_LEFT));
		{
			m.left = true;
			m.right = false;
			m.up = false;
			m.down = false;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m.left = false;
			m.right = true;
			m.up = false;
			m.down = false;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			m.left = false;
			m.right = false;
			m.up = true;
			m.down = false;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			m.left = false;
			m.right = false;
			m.up = false;
			m.down = true;
		}
		if (get_position().x <= 1) p.x += speed;
		if (get_position().x >= WIDTH - 41) p.x -= speed;
		if (get_position().y <= 1) p.y += speed;
		if (get_position().y >= HEIGHT - 41) p.y -= speed;
		if (m.left) p.x -= speed;
		if (m.right) p.x += speed;
		if (m.up) p.y -= speed;
		if (m.down) p.y += speed;
	}

	void handle_collision_with_wall(const labirynth& labirynth) {
		for (const auto& wall : labirynth.get_walls()) {
			if (wall.check_collision(get_bounding_box())) {
				// Cofnij ruch w przypadku kolizji
				if (m.left) p.x += speed;
				if (m.right) p.x -= speed;
				if (m.up) p.y += speed;
				if (m.down) p.y -= speed;

				break; // Tylko jedna kolizja jest mozliwa na raz
			}
		}
	}

	FloatRect get_bounding_box() const {
		CircleShape shape(15.f); // Rozmiar PacMana
		shape.setPosition(p.x, p.y);
		return shape.getGlobalBounds();
	}

	void draw(RenderWindow& window) const
	{
		CircleShape shape(15.f);
		shape.setFillColor(Color::Yellow);
		shape.setPosition(p.x, p.y);
		window.draw(shape);
	}

	position get_position() const
	{
		return p;
	}
};

class ghost : public pacman
{
private:
	Color color1;
	struct movement
	{
		bool left;
		bool right;
		bool up;
		bool down;
	};
public:
	movement m{};
	ghost(const float x, const float y, const Color color)
	{
		p.x = x;
		p.y = y;
		color1 = color;
	}

	void change_direction() {

		// Losowa zmiana kierunku o 90 stopni
		const int direction = rand() % 4;
		if (direction == 0) {
			m.left = true;
			m.right = m.up = m.down = false;
		}
		else if (direction == 1) {
			m.right = true;
			m.left = m.up = m.down = false;
		}
		else if (direction == 2) {
			m.up = true;
			m.left = m.right = m.down = false;
		}
		else {
			m.down = true;
			m.left = m.right = m.up = false;
		}
	}

	FloatRect get_bounding_box() const {
		CircleShape shape(15.f);
		shape.setPosition(p.x, p.y);
		return shape.getGlobalBounds();
	}

	void move(const pacman pacman, const wall& wall)
	{
		if (wall.check_collision(get_bounding_box())) {
			change_direction(); // Zmiana kierunku po kolizji
		}
		if (static_cast<int>(floor(sqrt(pow(pacman.get_position().x, 2) + pow(pacman.get_position().y, 2)))) % 200 == 0) { //Wylosuj nowy kierunek po przejechaniu 200 jednostek przez pacmana
			const float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			if (r < 0.25) {
				m.down = true;
				m.right = m.up = m.down = false;
			}
			else if (r < 0.5 && r >= 0.25)
			{
				m.left = true;
				m.right = m.up = m.down = false;
			}
			else if (r < 0.75 && r >= 0.5)
			{
				m.right = true;
				m.left = m.up = m.down = false;
			}
			else
			{
				m.up = true;
				m.left = m.right = m.down = false;
			}
		}
		if (get_position().x <= 1) p.x += SPEED / 2.;
		if (get_position().x >= WIDTH - 41) p.x -= SPEED / 2.;
		if (get_position().y <= 1) p.y += SPEED / 2.;
		if (get_position().y >= HEIGHT - 41) p.y -= SPEED / 2.;
		if (m.left) p.x -= SPEED / 2.;
		if (m.right) p.x += SPEED / 2.;
		if (m.up) p.y -= SPEED / 2.;
		if (m.down) p.y += SPEED / 2.;

	}
	Color get_color() const
	{
		return color1;
	}
	void draw(RenderWindow& window) const
	{
		CircleShape shape(15.f);
		shape.setFillColor(get_color());
		shape.setPosition(p.x, p.y);
		window.draw(shape);
	}
};

class punkt {
private:
	CircleShape shape;
public:
	punkt(const float x, const float y, const float radius = 10.f) {
		shape.setPosition(x, y);
		shape.setRadius(radius);
		shape.setFillColor(Color::White); // Mozesz ustawiæ dowolny kolor
	}
	// Zwraca bounding box punktu
	FloatRect get_bounding_box() const {
		return shape.getGlobalBounds();
	}
	// Rysuje punkt
	void draw(RenderWindow& window) const {
		window.draw(shape);
	}
};

class punkty {
private:
	std::vector<punkt> points; // Przechowywanie punktow
public:
	// Dodaje punkt do wektora
	void add_punkt(float x, float y, float radius = 10.f) {
		points.emplace_back(x, y, radius);
	}
	// Sprawdza, czy pacman koliduje z ktoryms z punktow
	bool check_collision(const FloatRect& pacman_bounds) {
		for (auto& point : points)
			if (pacman_bounds.intersects(point.get_bounding_box()))
				return true;
		return false;
	}
	// Rysuje wszystkie punkty
	void draw(RenderWindow& window) const {
		for (const auto& point : points)
			point.draw(window);
	}
	// Usuwa punkt (np. po zjedzeniu przez pacmana)
	void remove_punkt(const FloatRect& pacman_bounds) {
		points.erase(
			std::remove_if(points.begin(), points.end(),
				[&](const punkt& point) {return pacman_bounds.intersects(point.get_bounding_box()); }), points.end());
	}
	// Zwraca wektor punktow
	const std::vector<punkt>& get_punkty() const {
		return points;
	}
};

//class GamePoints {
//private:
//	vector<CircleShape> points;
//	int score;
//
//public:
//	GamePoints(const Labirynth& labirynth, const vector<Vector2f>& ghostStartingPositions) {
//		score = 0;
//
//		// Generowanie punktow w siatce 40x40
//		for (float y = 0; y < HEIGHT; y += 40.5) {
//			for (float x = 0; x < WIDTH; x += 40.5) {
//				FloatRect pointBounds(x + 10, y + 10 , 20, 20); // Obszar punktu
//
//				// Sprawd, czy punkt nie koliduje ze scianami
//				bool collidesWithWall = false;
//				for (const auto& wall : labirynth.get_walls()) {
//					if (wall.check_collision(pointBounds)) {
//						collidesWithWall = true;
//						break;
//					}
//				}
//
//				// Sprawd, czy punkt nie jest w strefie startowej duszkow
//			
//
//				if (!collidesWithWall) {
//					CircleShape point(10); // Promieñ 10 = srednica 20
//					point.setFillColor(Color::White);
//					point.setPosition(x, y);
//					points.push_back(point);
//				}
//			}
//		}
//	}
//
//	void checkCollisionWithPacman(const pacman& p) {
//		FloatRect pacmanBounds(p.get_position().x, p.get_position().y, 30, 30); // PacMan ma srednice 40
//
//		for (auto it = points.begin(); it != points.end();) {
//			if (it->getGlobalBounds().intersects(pacmanBounds)) {
//				it = points.erase(it); // Usuñ punkt
//				score++; // Zwieksz liczbe punktow
//			}
//			else {
//				++it;
//			}
//		}
//	}
//
//	void draw(RenderWindow& window) const {
//		for (const auto& point : points) {
//			window.draw(point);
//		}
//
//		// Rysowanie licznika punktow
//		Font font;
//		if (!font.loadFromFile("arial.ttf")) {
//			cerr << "Nie mozna zaladowaæ czcionki!\n";
//			return;
//		}
//
//		Text scoreText;
//		scoreText.setFont(font);
//		scoreText.setString("Score: " + to_string(score));
//		scoreText.setCharacterSize(24);
//		scoreText.setFillColor(Color::White);
//		scoreText.setPosition(10, 10);
//		window.draw(scoreText);
//	}
//};

void map1(labirynth& l, punkty& punkty);
void map2(labirynth& l, punkty& punkty);
void map3(labirynth& l, punkty& punkty);

void fill_with_punkty(punkty& punkty, const float x, const float y, const int n, const int m, const float distance) {
	for (int i = 0; i < n; i++) {
		punkty.add_punkt(x + i * distance, y);
		for (int j = 0; j < m; j++)
			punkty.add_punkt(x + i * distance, y + j * distance);
	}
}

void generate_pause_text(Font& font, Text& paused_text, Text& continue_text, Text& help_text, Text& quit_text, Text& confirmation) {
	if (!font.loadFromFile("bruno.ttf")) {
		cerr << "Failed to load font!" << endl;
		exit(-1);
	}

	paused_text.setFont(font);
	paused_text.setString("Game Paused");
	paused_text.setCharacterSize(60);
	paused_text.setFillColor(Color::White);
	paused_text.setPosition(WIDTH / 2 - paused_text.getGlobalBounds().width / 2, 50);

	continue_text.setFont(font);
	continue_text.setString("Press F1 to continue");
	continue_text.setCharacterSize(30);
	continue_text.setFillColor(Color::White);
	continue_text.setPosition(WIDTH / 2 - continue_text.getGlobalBounds().width / 2, 500);

	help_text.setFont(font);
	help_text.setString("\254Press F1 for help\n\254Use arrows to move\n\254Press escape to quit the game\n\nCollect the Points and avoid the Ghosts!");
	help_text.setCharacterSize(30);
	help_text.setFillColor(Color::White);
	help_text.setPosition(WIDTH / 2 - help_text.getGlobalBounds().width / 2, 200);

	quit_text.setFont(font);
	quit_text.setString("Are you sure you want to quit?");
	quit_text.setCharacterSize(60);
	quit_text.setFillColor(Color::White);
	quit_text.setPosition(WIDTH / 2 - quit_text.getGlobalBounds().width / 2, 50);

	confirmation.setFont(font);
	confirmation.setString("Press Y to quit or N to continue");
	confirmation.setCharacterSize(30);
	confirmation.setFillColor(Color::White);
	confirmation.setPosition(WIDTH / 2 - confirmation.getGlobalBounds().width / 2, 500);
}

void choose_map(RenderWindow& window, Font& font, int& choice, Sprite& backgroundSprite, RectangleShape& dark_background, Text& title, Text& author) {
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
		window.draw(backgroundSprite);
		window.draw(dark_background);
		window.draw(title);
		window.draw(map_text);
		window.draw(author);
		window.display();
	}
}

void display_menu(RenderWindow& window, Font& font, int& choice) {
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("back1.png")) {
		cerr << "Failed to load background image!" << endl;
		exit(-1);
	}
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
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
	author.setString("Nikodem Kozlowski 199239 ARiSS1\nTomasz Nazar 197613 ACiR3");
	author.setCharacterSize(15);
	author.setFillColor(Color::White);
	author.setPosition(WIDTH / 2 - author.getGlobalBounds().width / 2, 600);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
				choose_map(window, font, choice, backgroundSprite, dark_background, title, author);
				return;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close(); // Quit the game
		}

		window.clear();
		window.draw(backgroundSprite);
		window.draw(dark_background);
		window.draw(title);
		window.draw(start_text);
		window.draw(quit_text);
		window.draw(author);
		window.display();
	}
}

int main() {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");
	pacman p;
	ghost g(40, 40, Color::Green);
	ghost g1(1180, 40, Color::Red);
	ghost g2(40, 640, Color::Cyan);
	ghost g3(1180, 640, Color::White);
	ghost g4(40, 40, Color::Magenta);

	punkty punkty;
	labirynth labirynth;

	bool is_paused = false;
	bool quit_confirmation = false;

	// Load font for displaying "Paused" text
	Font font;
	Text paused_text, continue_text, help_text, quit_text, confirmation,score_text;
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
				if (wall.check_collision(g4.get_bounding_box())) g4.change_direction();
			}
			g.move(p, wall(0, 0, 0, 0));  // Duszki uzywaja swojej logiki
			g1.move(p, wall(0, 0, 0, 0)); // Uzycie pustego walla, bo logika jest w glownym
			g2.move(p, wall(0, 0, 0, 0));
			g3.move(p, wall(0, 0, 0, 0));
			g4.move(p, wall(0, 0, 0, 0));
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
		g4.draw(window);
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

//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include<windows.h>
//#include<iostream>
//#include <cstdlib>
//
//constexpr double SPEED = 0.5;
//constexpr int WIDTH = 760;
//constexpr int HEIGHT = 880;
//using namespace std;
//using namespace sf;
//
//class wall {
//public:
//	RectangleShape shape;
//
//	wall(const float x, const float y, const float width = 100.f, const float height = 40.f) {
//		shape.setSize(Vector2f(width, height));
//		shape.setFillColor(Color::Blue);
//		shape.setPosition(x, y);
//	}
//	bool check_collision(const FloatRect& bounding_box) const {
//		return shape.getGlobalBounds().intersects(bounding_box);
//	}
//	void draw(RenderWindow& window) const {
//		window.draw(shape);
//	}
//};
//
//class Labirynth {
//private:
//	std::vector<wall> walls;
//
//public:
//	Labirynth() {}
//
//	// Dodaje sciane do labiryntu (x,y,width,height)
//	void add_wall(float x, float y, float width, float height) {
//		walls.emplace_back(x, y, width, height);
//	}
//
//	// Sprawdza kolizje z dowolna sciana w labiryncie
//	bool check_collision(const FloatRect& bounding_box) const {
//		for (const auto& wall : walls) {
//			if (wall.check_collision(bounding_box)) {
//				return true;
//			}
//		}
//		return false;
//	}
//
//	// Rysuje wszystkie sciany w labiryncie
//	void draw(RenderWindow& window) const {
//		for (const auto& wall : walls) {
//			wall.draw(window);
//		}
//	}
//
//	const std::vector<wall>& get_walls() const {
//		return walls;
//	}
//};
//
//class pacman
//{
//private:
//	struct position
//	{
//		float x;
//		float y;
//	};
//
//	float speed;
//
//	struct movement
//	{
//		bool left;
//		bool right;
//		bool up;
//		bool down;
//	};
//public:
//	position p;
//	movement m{};
//	pacman()
//	{
//		movement m;
//		p.x = 40;
//		p.y = 40;
//		speed = SPEED;
//	}
//
//	void move()
//	{
//
//		if (GetAsyncKeyState(VK_LEFT))
//		{
//			m.left = true;
//			m.right = false;
//			m.up = false;
//			m.down = false;
//		}
//		if (GetAsyncKeyState(VK_RIGHT))
//		{
//			m.left = false;
//			m.right = true;
//			m.up = false;
//			m.down = false;
//
//		}
//		if (GetAsyncKeyState(VK_UP))
//		{
//			m.left = false;
//			m.right = false;
//			m.up = true;
//			m.down = false;
//		}
//		if (GetAsyncKeyState(VK_DOWN))
//		{
//			m.left = false;
//			m.right = false;
//			m.up = false;
//			m.down = true;
//		}
//		if (get_position().x <= 1) p.x += speed;
//		if (get_position().x >= WIDTH - 41) p.x -= speed;
//		if (get_position().y <= 1) p.y += speed;
//		if (get_position().y >= HEIGHT - 41) p.y -= speed;
//		if (m.left) p.x -= speed;
//		if (m.right) p.x += speed;
//		if (m.up) p.y -= speed;
//		if (m.down) p.y += speed;
//
//
//	}
//	void handle_collision_with_wall(const Labirynth& labirynth) {
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(get_bounding_box())) {
//				// Cofnij ruch w przypadku kolizji
//				if (m.left) p.x += speed;
//				if (m.right) p.x -= speed;
//				if (m.up) p.y += speed;
//				if (m.down) p.y -= speed;
//
//				break; // Tylko jedna kolizja jest mozliwa na raz
//			}
//		}
//	}
//	FloatRect get_bounding_box() const {
//		CircleShape shape(15.f); // Rozmiar PacMana
//		shape.setPosition(p.x, p.y);
//		return shape.getGlobalBounds();
//	}
//
//
//	void draw(RenderWindow& window) const
//	{
//		CircleShape shape(15.f);
//		shape.setFillColor(Color::Yellow);
//		shape.setPosition(p.x, p.y);
//		window.draw(shape);
//	}
//	position get_position() const
//	{
//		return p;
//	}
//
//};
//
//
//
//
//
//
//// duszki podazajace za pacmanem
//class ghost : public pacman
//{
//private:
//	Color color1;
//	struct movement
//	{
//		bool left;
//		bool right;
//		bool up;
//		bool down;
//	};
//	movement currentDirection;
//	bool isBlocked;  // Flaga informujaca, czy duszek jest zablokowany przez sciane
//
//public:
//	ghost(const int x, const int y, const Color color)
//	{
//		p.x = x;
//		p.y = y;
//		color1 = color;
//		currentDirection = { false, true, false, false }; // Domyslny kierunek: w prawo
//		isBlocked = false;  // Poczatkowo duszek nie jest zablokowany
//	}
//
//	// Funkcja zmieniajaca kierunek o 90 stopni zgodnie z ruchem wskazowek zegara
//	void change_direction() {
//		if (currentDirection.left) {
//			currentDirection.left = false;
//			currentDirection.up = true;
//			currentDirection.right = false;
//			currentDirection.down = false;
//		}
//		else if (currentDirection.up) {
//			currentDirection.left = false;
//			currentDirection.up = false;
//			currentDirection.right = true;
//			currentDirection.down = false;
//		}
//		else if (currentDirection.right) {
//			currentDirection.left = false;
//			currentDirection.up = false;
//			currentDirection.right = false;
//			currentDirection.down = true;
//		}
//		else if (currentDirection.down) {
//			currentDirection.left = true;
//			currentDirection.up = false;
//			currentDirection.right = false;
//			currentDirection.down = false;
//		}
//	}
//
//	// Funkcja sprawdzajaca, czy duszek ma zblizyæ sie do PacMana
//	void move_towards_pacman(const pacman& pacman, const Labirynth& labirynth)
//	{
//		// Obliczanie roznicy pozycji w obu osiach
//		float dx = pacman.get_position().x - p.x;
//		float dy = pacman.get_position().y - p.y;
//
//		// Normalizacja wektora kierunku
//		float distance = sqrt(dx * dx + dy * dy); // Odleglosæ do PacMana
//		dx /= distance;
//		dy /= distance;
//
//		// Zmiana kierunku na podstawie PacMana
//		if (abs(dx) > abs(dy)) { // Jezeli ruch w osi X jest wiekszy
//			if (dx > 0) {
//				currentDirection.left = false;
//				currentDirection.right = true;
//			}
//			else {
//				currentDirection.left = true;
//				currentDirection.right = false;
//			}
//			currentDirection.up = false;
//			currentDirection.down = false;
//		}
//		else { // Jezeli ruch w osi Y jest wiekszy
//			if (dy > 0) {
//				currentDirection.down = true;
//				currentDirection.up = false;
//			}
//			else {
//				currentDirection.up = true;
//				currentDirection.down = false;
//			}
//			currentDirection.left = false;
//			currentDirection.right = false;
//		}
//
//		// Sprawdzanie kolizji w wybranym kierunku
//		if (currentDirection.left && !wall_collision_left(labirynth)) {
//			p.x -= SPEED / 2.0; // Ruch w lewo
//		}
//		else if (currentDirection.right && !wall_collision_right(labirynth)) {
//			p.x += SPEED / 2.0; // Ruch w prawo
//		}
//		else if (currentDirection.up && !wall_collision_up(labirynth)) {
//			p.y -= SPEED / 2.0; // Ruch w gore
//		}
//		else if (currentDirection.down && !wall_collision_down(labirynth)) {
//			p.y += SPEED / 2.0; // Ruch w dol
//		}
//		else {
//			// Jesli napotka sciane w wybranym kierunku, sprobuj innego
//			if (currentDirection.left && wall_collision_left(labirynth)) {
//				// Sprawd inne kierunki
//				if (!wall_collision_up(labirynth)) {
//					p.y -= SPEED / 2.0; // Ruch w gore
//				}
//				else if (!wall_collision_down(labirynth)) {
//					p.y += SPEED / 2.0; // Ruch w dol
//				}
//				else if (!wall_collision_right(labirynth)) {
//					p.x += SPEED / 2.0; // Ruch w prawo
//				}
//			}
//			else if (currentDirection.right && wall_collision_right(labirynth)) {
//				// Sprawd inne kierunki
//				if (!wall_collision_up(labirynth)) {
//					p.y -= SPEED / 2.0; // Ruch w gore
//				}
//				else if (!wall_collision_down(labirynth)) {
//					p.y += SPEED / 2.0; // Ruch w dol
//				}
//				else if (!wall_collision_left(labirynth)) {
//					p.x -= SPEED / 2.0; // Ruch w lewo
//				}
//			}
//			else if (currentDirection.up && wall_collision_up(labirynth)) {
//				// Sprawd inne kierunki
//				if (!wall_collision_left(labirynth)) {
//					p.x -= SPEED / 2.0; // Ruch w lewo
//				}
//				else if (!wall_collision_right(labirynth)) {
//					p.x += SPEED / 2.0; // Ruch w prawo
//				}
//				else if (!wall_collision_down(labirynth)) {
//					p.y += SPEED / 2.0; // Ruch w dol
//				}
//			}
//			else if (currentDirection.down && wall_collision_down(labirynth)) {
//				// Sprawd inne kierunki
//				if (!wall_collision_left(labirynth)) {
//					p.x -= SPEED / 2.0; // Ruch w lewo
//				}
//				else if (!wall_collision_right(labirynth)) {
//					p.x += SPEED / 2.0; // Ruch w prawo
//				}
//				else if (!wall_collision_up(labirynth)) {
//					p.y -= SPEED / 2.0; // Ruch w gore
//				}
//			}
//		}
//
//		// Sprawdzanie kolizji z granicami ekranu
//		if (get_position().x <= 1) p.x += SPEED / 2.0;
//		if (get_position().x >= WIDTH - 41) p.x -= SPEED / 2.0;
//		if (get_position().y <= 1) p.y += SPEED / 2.0;
//		if (get_position().y >= HEIGHT - 41) p.y -= SPEED / 2.0;
//	}
//
//	// Sprawdzanie kolizji w lewo
//	bool wall_collision_left(const Labirynth& labirynth) {
//		FloatRect ghostBounds = get_bounding_box();
//		ghostBounds.left -= SPEED / 2.0;
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(ghostBounds)) return true;
//		}
//		return false;
//	}
//
//	// Sprawdzanie kolizji w prawo
//	bool wall_collision_right(const Labirynth& labirynth) {
//		FloatRect ghostBounds = get_bounding_box();
//		ghostBounds.left += SPEED / 2.0;
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(ghostBounds)) return true;
//		}
//		return false;
//	}
//
//	// Sprawdzanie kolizji w gore
//	bool wall_collision_up(const Labirynth& labirynth) {
//		FloatRect ghostBounds = get_bounding_box();
//		ghostBounds.top -= SPEED / 2.0;
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(ghostBounds)) return true;
//		}
//		return false;
//	}
//
//	// Sprawdzanie kolizji w dol
//	bool wall_collision_down(const Labirynth& labirynth) {
//		FloatRect ghostBounds = get_bounding_box();
//		ghostBounds.top += SPEED / 2.0;
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(ghostBounds)) return true;
//		}
//		return false;
//	}
//
//	// Rysowanie duszka
//	void draw(RenderWindow& window) const
//	{
//		CircleShape shape(15.f);
//		shape.setFillColor(get_color());
//		shape.setPosition(p.x, p.y);
//		window.draw(shape);
//	}
//
//	// Uzyskiwanie koloru duszka
//	Color get_color() const
//	{
//		return color1;
//	}
//
//	// Uzyskiwanie bounding box dla duszka
//	FloatRect get_bounding_box() const {
//		CircleShape shape(15.f);
//		shape.setPosition(p.x, p.y);
//		return shape.getGlobalBounds();
//	}
//};
//
//
//class GamePoints {
//private:
//	vector<CircleShape> points;
//	int score;
//
//public:
//	GamePoints(const Labirynth& labirynth, const vector<Vector2f>& ghostStartingPositions) {
//		score = 0;
//
//		// Generowanie punktow w siatce 40x40
//		for (float y = 0; y < HEIGHT; y += 40.5) {
//			for (float x = 0; x < WIDTH; x += 40.5) {
//				FloatRect pointBounds(x + 10, y + 10, 20, 20); // Obszar punktu
//
//				// Sprawd, czy punkt nie koliduje ze scianami
//				bool collidesWithWall = false;
//				for (const auto& wall : labirynth.get_walls()) {
//					if (wall.check_collision(pointBounds)) {
//						collidesWithWall = true;
//						break;
//					}
//				}
//
//				// Sprawd, czy punkt nie jest w strefie startowej duszkow
//
//
//				if (!collidesWithWall) {
//					CircleShape point(10); // Promieñ 10 = srednica 20
//					point.setFillColor(Color::White);
//					point.setPosition(x, y);
//					points.push_back(point);
//				}
//			}
//		}
//	}
//
//	void checkCollisionWithPacman(const pacman& p) {
//		FloatRect pacmanBounds(p.get_position().x, p.get_position().y, 30, 30); // PacMan ma srednice 40
//
//		for (auto it = points.begin(); it != points.end();) {
//			if (it->getGlobalBounds().intersects(pacmanBounds)) {
//				it = points.erase(it); // Usuñ punkt
//				score++; // Zwieksz liczbe punktow
//			}
//			else {
//				++it;
//			}
//		}
//	}
//
//	void draw(RenderWindow& window) const {
//		for (const auto& point : points) {
//			window.draw(point);
//		}
//
//		// Rysowanie licznika punktow
//		Font font;
//		if (!font.loadFromFile("arial.ttf")) {
//			cerr << "Nie mozna zaladowaæ czcionki!\n";
//			return;
//		}
//
//		Text scoreText;
//		scoreText.setFont(font);
//		scoreText.setString("Score: " + to_string(score));
//		scoreText.setCharacterSize(24);
//		scoreText.setFillColor(Color::White);
//		scoreText.setPosition(10, 10);
//		window.draw(scoreText);
//	}
//};
//
//void map4(Labirynth& l);
//int main() {
//	RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");
//	pacman p;
//	
//	ghost g(360, 400, Color::Green);
//	ghost g1(690, 40, Color::Red);
//	ghost g2(40, 810, Color::Cyan);
//	ghost g3(690, 810, Color::White);
//	ghost g4(40, 40, Color::Magenta);
//	
//	
//	// Tworzenie labiryntu
//	Labirynth labirynth;
//
//	
//	map4(labirynth);
//
//	vector<Vector2f> ghostStartingPositions = {
//		{40, 40},{690, 40},{40, 810},{690, 810},{40, 40}
//	};
//	GamePoints points(labirynth, ghostStartingPositions);
//
//
//	while (window.isOpen()) {
//		Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == Event::Closed)
//				window.close();
//		}
//
//		// Ruch PacMana
//		p.move();
//		p.handle_collision_with_wall(labirynth);
//		points.checkCollisionWithPacman(p);
//
//
//		// Ruch duszkow z uwzglednieniem kolizji z labiryntem
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(g.get_bounding_box())) g.change_direction();
//			if (wall.check_collision(g1.get_bounding_box())) g1.change_direction();
//			if (wall.check_collision(g2.get_bounding_box())) g2.change_direction();
//			if (wall.check_collision(g3.get_bounding_box())) g3.change_direction();
//			if (wall.check_collision(g4.get_bounding_box())) g4.change_direction();
//		}
//
//		g.move_towards_pacman(p, labirynth);  // Duszki uzywaja swojej logiki
//		g1.move_towards_pacman(p, labirynth); // Uzycie pustego walla, bo logika jest w glownym
//		g2.move_towards_pacman(p, labirynth);
//		g3.move_towards_pacman(p, labirynth);
//		g4.move_towards_pacman(p, labirynth);
//
//		// Rysowanie
//		window.clear();
//		labirynth.draw(window);
//		points.draw(window);
//		g.draw(window);
//		g1.draw(window);
//		g2.draw(window);
//		g3.draw(window);
//		g4.draw(window);
//		p.draw(window);
//		window.display();
//	}
//
//	return 0;
//}
//void map4(Labirynth& l)
//{
//	l.add_wall(0, 0, 760, 40); // sciana pozioma gorna
//	l.add_wall(0, 40, 40, 800); // sciana pionowa lewa
//	l.add_wall(0, 840, 760, 40); // sciana pozioma dolna
//	l.add_wall(720, 40, 40, 800); // sciana pionowa prawa
//
//	l.add_wall(80, 80, 80, 80);
//	l.add_wall(200, 80, 120, 80);
//	l.add_wall(360, 40, 40, 120);
//	l.add_wall(440, 80, 120, 80);
//	l.add_wall(600, 80, 80, 80);
//	l.add_wall(80, 200, 80, 40);
//	l.add_wall(200, 200, 40, 200);
//	l.add_wall(280, 200, 200, 40);
//	l.add_wall(520, 200, 40, 200);
//	l.add_wall(600, 200, 80, 40);
//	l.add_wall(40, 280, 120, 120);
//	l.add_wall(240, 280, 80, 40);
//	l.add_wall(360, 240, 40, 80);
//	l.add_wall(440, 280, 80, 40);
//	l.add_wall(600, 280, 120, 120);
//	l.add_wall(280, 360, 80, 40);
//	l.add_wall(400, 360, 80, 40);
//	l.add_wall(280, 400, 40, 40);
//	l.add_wall(440, 400, 40, 40);
//	l.add_wall(40, 440, 120, 120);
//	l.add_wall(200, 440, 40, 120);
//	l.add_wall(280, 440, 200, 40);
//	l.add_wall(520, 440, 40, 120);
//	l.add_wall(600, 440, 120, 120);
//	l.add_wall(280, 520, 200, 40);
//	l.add_wall(360, 560, 40, 80);
//	l.add_wall(80, 600, 80, 40);
//	l.add_wall(200, 600, 120, 40);
//	l.add_wall(440, 600, 120, 40);
//	l.add_wall(600, 600, 80, 40);
//	l.add_wall(120, 640, 40, 80);
//	l.add_wall(600, 640, 40, 80);
//	l.add_wall(40, 680, 40, 40);
//	l.add_wall(200, 680, 40, 80);
//	l.add_wall(280, 680, 200, 40);
//	l.add_wall(520, 680, 40, 80);
//	l.add_wall(680, 680, 40, 40);
//	l.add_wall(360, 720, 40, 80);
//	l.add_wall(80, 760, 240, 40);
//	l.add_wall(440, 760, 240, 40);
//}
