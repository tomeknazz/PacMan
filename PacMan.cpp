//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include<windows.h>
//#include<iostream>
//#include <cstdlib>
//
//constexpr double SPEED = 0.05;
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
//class labirynth {
//private:
//	std::vector<wall> walls;
//
//public:
//	labirynth() {}
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
//	// Rysuje wszystkie œciany w labiryncie
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
//	void handle_collision_with_wall(const labirynth& labirynth) {
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(get_bounding_box())) {
//				// Cofnij ruch w przypadku kolizji
//				if (m.left) p.x += speed;
//				if (m.right) p.x -= speed;
//				if (m.up) p.y += speed;
//				if (m.down) p.y -= speed;
//
//				break; // Tylko jedna kolizja jest mo¿liwa na raz
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
//};
//
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
//public:
//	movement m{};
//	ghost(const int x, const int y, const Color color)
//	{
//		p.x = x;
//		p.y = y;
//		color1 = color;
//	}
//
//	void change_direction() {
//
//		// Losowa zmiana kierunku o 90 stopni
//		const int direction = rand() % 4;
//		if (direction == 0) {
//			m.left = true;
//			m.right = m.up = m.down = false;
//		}
//		else if (direction == 1) {
//			m.right = true;
//			m.left = m.up = m.down = false;
//		}
//		else if (direction == 2) {
//			m.up = true;
//			m.left = m.right = m.down = false;
//		}
//		else {
//			m.down = true;
//			m.left = m.right = m.up = false;
//		}
//	}
//
//	FloatRect get_bounding_box() const {
//		CircleShape shape(15.f);
//		shape.setPosition(p.x, p.y);
//		return shape.getGlobalBounds();
//	}
//
//	void move(const pacman pacman, const wall& wall)
//	{
//		if (wall.check_collision(get_bounding_box())) {
//			change_direction(); // Zmiana kierunku po kolizji
//		}
//		if (static_cast<int>(floor(sqrt(pow(pacman.get_position().x, 2) + pow(pacman.get_position().y, 2)))) % 200 == 0) {
//			const float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Generate a random float between 0 and 1
//			if (r < 0.25) {
//				m.down = true;
//				m.right = m.up = m.down = false;
//			}
//			else if (r < 0.5 && r >= 0.25)
//			{
//				m.left = true;
//				m.right = m.up = m.down = false;
//			}
//			else if (r < 0.75 && r >= 0.5)
//			{
//				m.right = true;
//				m.left = m.up = m.down = false;
//			}
//			else
//			{
//				m.up = true;
//				m.left = m.right = m.down = false;
//			}
//		}
//		if (get_position().x <= 1) p.x += SPEED / 2.;
//		if (get_position().x >= WIDTH - 41) p.x -= SPEED / 2.;
//		if (get_position().y <= 1) p.y += SPEED / 2.;
//		if (get_position().y >= HEIGHT - 41) p.y -= SPEED / 2.;
//		if (m.left) p.x -= SPEED / 2.;
//		if (m.right) p.x += SPEED / 2.;
//		if (m.up) p.y -= SPEED / 2.;
//		if (m.down) p.y += SPEED / 2.;
//
//	}
//	Color get_color() const
//	{
//		return color1;
//	}
//	void draw(RenderWindow& window) const
//	{
//		CircleShape shape(15.f);
//		shape.setFillColor(get_color());
//		shape.setPosition(p.x, p.y);
//		window.draw(shape);
//	}
//};
//
//void map1(labirynth& l);
//void map2(labirynth& l);
//void map3(labirynth& l);
//void map4(labirynth& l);
//
//int main() {
//	RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");
//	pacman p;
//	ghost g(40, 40, Color::Green);
//	ghost g1(690, 40, Color::Red);
//	ghost g2(40, 810, Color::Cyan);
//	ghost g3(690, 810, Color::White);
//	ghost g4(40, 40, Color::Magenta);
//
//	// Tworzenie labiryntu
//	labirynth labirynth;
//
//	/*map1(labirynth);*/
//	/*map2(labirynth);*/
//	/*map3(labirynth);*/
//	map4(labirynth);
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
//
//		// Ruch duszków z uwzglêdnieniem kolizji z labiryntem
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(g.get_bounding_box())) g.change_direction();
//			if (wall.check_collision(g1.get_bounding_box())) g1.change_direction();
//			if (wall.check_collision(g2.get_bounding_box())) g2.change_direction();
//			if (wall.check_collision(g3.get_bounding_box())) g3.change_direction();
//			if (wall.check_collision(g4.get_bounding_box())) g4.change_direction();
//		}
//
//		g.move(p, wall(0, 0, 0, 0));  // Duszki u¿ywaj¹ swojej logiki
//		g1.move(p, wall(0, 0, 0, 0)); // U¿ycie pustego walla, bo logika jest w g³ównym
//		g2.move(p, wall(0, 0, 0, 0));
//		g3.move(p, wall(0, 0, 0, 0));
//		g4.move(p, wall(0, 0, 0, 0));
//
//		// Rysowanie
//		window.clear();
//		labirynth.draw(window); // Rysowanie labiryntu
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
//
//void map1(labirynth& l)
//{
//	//ramki
//	l.add_wall(0, 0, 1260, 30); // Œciana pozioma gorna
//	l.add_wall(0, 30, 30, 660); // Œciana pionowa lewa
//	l.add_wall(0, 690, 1260, 30); // Œciana pozioma dolna
//	l.add_wall(1230, 30, 30, 660); // Œciana pionowa prawa
//
//	//4 rogi
//	//lewy gora
//	l.add_wall(110, 110, 30, 200); //pionowa
//	l.add_wall(140, 110, 80, 30); //pozioma
//	//lewy dol
//	l.add_wall(110, 410, 30, 200);//pionowa
//	l.add_wall(140, 580, 80, 30);//pozioma
//	//prawy gora
//	l.add_wall(1120, 110, 30, 200);//pionowa
//	l.add_wall(1040, 110, 80, 30);//pozioma
//
//	//prawy dol
//	l.add_wall(1120, 410, 30, 200); //pionowa
//	l.add_wall(1040, 580, 80, 30); //pozioma
//
//
//	//4 bolce pionowe
//	l.add_wall(300, 30, 30, 110); //lewy gora
//	l.add_wall(930, 30, 30, 110); //prawy gora
//	l.add_wall(300, 580, 30, 110); //lewy dol
//	l.add_wall(930, 580, 30, 110); //prawy dol
//
//	//6 bolce poziome
//	l.add_wall(220, 230, 110, 30); //lewy gorny
//	l.add_wall(220, 345, 190, 30); //lewy srodek
//	l.add_wall(220, 460, 110, 30); //lewy dol
//	l.add_wall(930, 230, 110, 30); //prawy gora
//	l.add_wall(850, 345, 190, 30); //prawy srodek
//	l.add_wall(930, 460, 110, 30); //prawy dol
//
//	//2 dlugie pionowe
//	l.add_wall(410, 230, 30, 260);//lewy
//	l.add_wall(820, 230, 30, 260);//prawy
//
//	//2 dlugie poziome
//	l.add_wall(410, 110, 440, 30);//gorny
//	l.add_wall(410, 580, 440, 30);//dolny
//
//	//srodek
//	l.add_wall(520, 140, 30, 170);//pionowy gorny
//	l.add_wall(520, 410, 30, 170);//pionowy dolny
//	l.add_wall(630, 230, 30, 260);//pionowy srodek
//	l.add_wall(660, 230, 80, 30);//poziomy gora
//	l.add_wall(660, 345, 80, 30);//poziomy srodek
//	l.add_wall(660, 460, 80, 30);//poziomy dol
//}
//void map2(labirynth& l)
//{	//ramki
//	l.add_wall(0, 0, 1260, 20); // Œciana pozioma gorna
//	l.add_wall(0, 20, 20, 680); // Œciana pionowa lewa
//	l.add_wall(0, 700, 1260, 20); // Œciana pozioma dolna
//	l.add_wall(1240, 20, 20, 680); // Œciana pionowa prawa
//	///lewa strona
//	l.add_wall(100, 600, 120, 20);//poziomy
//	l.add_wall(100, 520, 20, 80);//pionowy
//
//	l.add_wall(300, 600, 20, 100);//pionowy
//
//	l.add_wall(400, 600, 100, 20);//poziomy
//	l.add_wall(500, 500, 20, 120);//pionowy
//	l.add_wall(400, 500, 20, 20);//kwadrat
//
//	l.add_wall(200, 500, 120, 20);//poziomy cienki
//	l.add_wall(200, 400, 20, 100);//pionowy 
//	l.add_wall(100, 400, 100, 40);//poziomy gruby
//
//	l.add_wall(300, 400, 120, 20);//poziomy lewy
//	l.add_wall(300, 200, 20, 200);//pionowy lewy
//	l.add_wall(500, 200, 20, 220);//pionowy prawy
//	l.add_wall(400, 300, 100, 20);//poziomy prawy
//	l.add_wall(400, 200, 20, 20);//kwadrat
//
//	l.add_wall(20, 280, 200, 40);//gruby poziomy
//	l.add_wall(200, 200, 20, 80);//pionowy dolny
//	l.add_wall(100, 100, 20, 100);//pionowy gorny
//	l.add_wall(120, 100, 100, 20);//poziomy gorny
//
//	l.add_wall(300, 20, 20, 100);//pionowy samotnik
//	l.add_wall(400, 100, 120, 20);//poziomy samotnik
//
//	//srodek
//	l.add_wall(600, 20, 60, 100);//gorny prostokat
//	l.add_wall(600, 200, 60, 60);//gorny kwadrat
//	l.add_wall(600, 340, 60, 40);//srodkowy
//	l.add_wall(600, 460, 60, 60);//dolny kwadrat
//	l.add_wall(600, 600, 60, 100);//dolny prostokat
//
//
//	//prawa strona
//	l.add_wall(740, 100, 120, 20);//poziomy lewy
//	l.add_wall(740, 120, 20, 100);//pionowy lewy
//	l.add_wall(840, 200, 20, 20);//kwadrat
//
//	l.add_wall(940, 20, 20, 100);//pionowy samotny
//	l.add_wall(1040, 100, 120, 20);//poziomy rog
//	l.add_wall(1140, 120, 20, 80);//pionowy rog
//
//	l.add_wall(940, 200, 120, 20);//poziomy
//	l.add_wall(1040, 220, 20, 100);//pionowy cienki
//	l.add_wall(1060, 280, 100, 40);//poziomy gruby
//
//	l.add_wall(740, 300, 20, 220);//pionowy
//	l.add_wall(760, 400, 100, 20);//poziomy
//	l.add_wall(840, 300, 120, 20);//pionowy
//	l.add_wall(940, 320, 20, 200);//poziomy
//	l.add_wall(840, 500, 20, 20);//kwadrat
//
//	l.add_wall(1040, 400, 200, 40);//gruby ze sciany
//	l.add_wall(1040, 440, 20, 80);//pionowy
//
//	l.add_wall(740, 600, 120, 20);//poziomy samotnik
//	l.add_wall(940, 600, 20, 100);//pionowy samotnik
//	l.add_wall(1040, 600, 120, 20);//poziomy
//	l.add_wall(1140, 520, 20, 80);
//}
//void map3(labirynth& l)
//{
//	//ramki
//	l.add_wall(0, 0, 1260, 10); // Œciana pozioma gorna
//	l.add_wall(0, 10, 10, 700); // Œciana pionowa lewa
//	l.add_wall(0, 710, 1260, 10); // Œciana pozioma dolna
//	l.add_wall(1250, 10, 10, 700); // Œciana pionowa prawa
//
//	//lewy rog
//	 l.add_wall(10, 510, 80, 20);//maly bolec ze sciany poziomy
//	 l.add_wall(270, 410, 100, 20);//samotny poziomy
//
//	//niepelnosprawne f
//	l.add_wall(90, 610, 280, 20);//poziomy z f
//	l.add_wall(270, 510, 20, 100);//pionowy z f
//	
//	//odwrocona elka
//	l.add_wall(170, 410, 20, 120);//pionowy z odwroconej elki
//	l.add_wall(90, 410, 80, 20);//poziomy z odwroconej elki
//
//	//kinole
//	l.add_wall(370, 510, 180, 20);//kinol dolny poziome
//	l.add_wall(450,530,20,100);//kinol dolny pionowe
//
//	l.add_wall(450,330,20,100);//kinol pionowe gorne
//	l.add_wall(370,310,180,20);//kinol poziome gora
//
//	l.add_wall(370, 90, 180, 20);//kinol najwyzszy poziome
//	l.add_wall(450, 110, 20, 120);//kinol najwyzszy pionowe
//
//	//prawy rog
//	l.add_wall(910,610,85,20); // poziomy dol 1
//	l.add_wall(1075, 610, 85, 20);//poziomy dol 2
//	l.add_wall(830,510,330,20);//poziomy gora
//	l.add_wall(910, 410, 20, 100);//pionowy gora
//	l.add_wall(550, 410, 100, 20);
//	l.add_wall(1000, 410, 160, 20);
//	//niepelnosprawne f
//	l.add_wall(550,610,280,20);//poziomy z f
//	l.add_wall(630,510,20,100);//pionowy z f
//
//	
//
//	//odwr elka
//	l.add_wall(730,410,20,120);//pionowy z elki
//	l.add_wall(750, 410, 80, 20);//poziomy z elki
//
//	//srodek
//	l.add_wall(270, 230, 20, 100);//pionowy lewy
//	l.add_wall(270, 210, 100, 20);//poziomy lewy
//	l.add_wall(630, 230, 20, 100);//pionowy prawy
//	l.add_wall(550, 210, 100, 20);//poziomy prawy
//
//
//	//lewy gora
//	l.add_wall(90, 90, 20, 240);//pionowy
//	l.add_wall(110, 210, 80, 20);//poziomy
//	l.add_wall(190, 10, 20, 80);//pionowy lewy gora
//	l.add_wall(190, 90, 100, 20);//poziomy lewy gora
//
//	//prawy gora
//	l.add_wall(630, 90, 100, 20);//poziomy prawy gora
//	l.add_wall(710, 10, 20, 80);//pionowy prawy gora
//	l.add_wall(730, 210, 80, 20);//poziomy
//	l.add_wall(810, 90, 20, 240);//pionowy
//	//kwadrat duzy
//	l.add_wall(890, 90, 20, 240);//lewy bok
//	l.add_wall(910, 90, 260, 20);//gora
//	l.add_wall(1150, 90, 20, 240);//prawy bok
//	l.add_wall(910, 310, 80, 20);//lewy dol
//	l.add_wall(1070, 310, 100, 20);//prawy dol
//	l.add_wall(980, 170, 100, 80);
//}  
//void map4(labirynth& l) 
//{
//	l.add_wall(0, 0, 760, 40); // Œciana pozioma gorna
//	l.add_wall(0, 40, 40, 800); // Œciana pionowa lewa
//	l.add_wall(0, 840, 760, 40); // Œciana pozioma dolna
//	l.add_wall(720, 40, 40, 800); // Œciana pionowa prawa
//
//	l.add_wall(80,80,80,80);
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
//}


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<windows.h>
#include<iostream>
#include <cstdlib>

constexpr double SPEED = 0.05;
constexpr int WIDTH = 1260;
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

class Labirynth {
private:
	std::vector<wall> walls;

public:
	Labirynth() {}

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

	// Rysuje wszystkie œciany w labiryncie
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
		movement m;
		p.x = 40;
		p.y = 40;
		speed = SPEED;
	}

	void move()
	{

		if (GetAsyncKeyState(VK_LEFT))
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
	void handle_collision_with_wall(const Labirynth& labirynth) {
		for (const auto& wall : labirynth.get_walls()) {
			if (wall.check_collision(get_bounding_box())) {
				// Cofnij ruch w przypadku kolizji
				if (m.left) p.x += speed;
				if (m.right) p.x -= speed;
				if (m.up) p.y += speed;
				if (m.down) p.y -= speed;

				break; // Tylko jedna kolizja jest mo¿liwa na raz
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
	ghost(const int x, const int y, const Color color)
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
		if (static_cast<int>(floor(sqrt(pow(pacman.get_position().x, 2) + pow(pacman.get_position().y, 2)))) % 200 == 0) {
			const float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Generate a random float between 0 and 1
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
class Punkt {
private:
	CircleShape shape;

public:
	Punkt(float x, float y, float radius = 10.f) {
		shape.setPosition(x, y);
		shape.setRadius(radius);
		shape.setFillColor(Color::White); // Mo¿esz ustawiæ dowolny kolor
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

class Punkty {
private:
	std::vector<Punkt> points; // Przechowywanie punktów

public:
	// Dodaje punkt do wektora
	void add_punkt(float x, float y, float radius = 10.f) {
		points.emplace_back(x, y, radius);
	}

	// Sprawdza, czy pacman koliduje z którymœ z punktów
	bool check_collision(const FloatRect& pacman_bounds) {
		for (auto& point : points) {
			if (pacman_bounds.intersects(point.get_bounding_box())) {
				return true;
			}
		}
		return false;
	}

	// Rysuje wszystkie punkty
	void draw(RenderWindow& window) const {
		for (const auto& point : points) {
			point.draw(window);
		}
	}

	// Usuwa punkt (np. po zjedzeniu przez pacmana)
	void remove_punkt(const FloatRect& pacman_bounds) {
		points.erase(
			std::remove_if(points.begin(), points.end(),
				[&](const Punkt& point) {
					return pacman_bounds.intersects(point.get_bounding_box());
				}),
			points.end());
	}

	// Zwraca wektor punktów
	const std::vector<Punkt>& get_punkty() const {
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
//		// Generowanie punktów w siatce 40x40
//		for (float y = 0; y < HEIGHT; y += 40.5) {
//			for (float x = 0; x < WIDTH; x += 40.5) {
//				FloatRect pointBounds(x + 10, y + 10 , 20, 20); // Obszar punktu
//
//				// SprawdŸ, czy punkt nie koliduje ze œcianami
//				bool collidesWithWall = false;
//				for (const auto& wall : labirynth.get_walls()) {
//					if (wall.check_collision(pointBounds)) {
//						collidesWithWall = true;
//						break;
//					}
//				}
//
//				// SprawdŸ, czy punkt nie jest w strefie startowej duszków
//			
//
//				if (!collidesWithWall) {
//					CircleShape point(10); // Promieñ 10 = œrednica 20
//					point.setFillColor(Color::White);
//					point.setPosition(x, y);
//					points.push_back(point);
//				}
//			}
//		}
//	}
//
//	void checkCollisionWithPacman(const pacman& p) {
//		FloatRect pacmanBounds(p.get_position().x, p.get_position().y, 30, 30); // PacMan ma œrednicê 40
//
//		for (auto it = points.begin(); it != points.end();) {
//			if (it->getGlobalBounds().intersects(pacmanBounds)) {
//				it = points.erase(it); // Usuñ punkt
//				score++; // Zwiêksz liczbê punktów
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
//		// Rysowanie licznika punktów
//		Font font;
//		if (!font.loadFromFile("arial.ttf")) {
//			cerr << "Nie mo¿na za³adowaæ czcionki!\n";
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


void map1(Labirynth& l);
void map2(Labirynth& l);
void map3(Labirynth& l);


int main() {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");
	pacman p;
	ghost g(40, 40, Color::Green);
	ghost g1(1180, 40, Color::Red);
	ghost g2(40, 640, Color::Cyan);
	ghost g3(1180, 640, Color::White);
	ghost g4(40, 40, Color::Magenta);
		

	// Tworzenie labiryntu
	Labirynth labirynth;

	//map1(labirynth);
	map2(labirynth);
	/*map3(labirynth);*/

	//mapa 2
	Punkty punkty;
	//1 WIERSZ
	punkty.add_punkt(100, 50);
	punkty.add_punkt(150, 50);
	punkty.add_punkt(200, 50);
	punkty.add_punkt(250, 50);
	punkty.add_punkt(350, 50);
	punkty.add_punkt(400, 50);
	punkty.add_punkt(450, 50);
	punkty.add_punkt(500, 50);
	punkty.add_punkt(550, 50);
	punkty.add_punkt(690,50);
	punkty.add_punkt(740, 50);
	punkty.add_punkt(790, 50);
	punkty.add_punkt(840, 50);
	punkty.add_punkt(890,50);
	punkty.add_punkt(990, 50);
	punkty.add_punkt(1040, 50);
	punkty.add_punkt(1090, 50);
	punkty.add_punkt(1140, 50);
	punkty.add_punkt(1190, 50);

	//2 wiersz
	punkty.add_punkt(50, 100);
	punkty.add_punkt(250, 100);
	punkty.add_punkt(350, 100);
	punkty.add_punkt(550, 100);
	punkty.add_punkt(690, 100);
	punkty.add_punkt(890, 100);
	punkty.add_punkt(990, 100);
	punkty.add_punkt(1190, 100);


	//3 wiersz
	punkty.add_punkt(50, 150);
	punkty.add_punkt(150, 150);
	punkty.add_punkt(200, 150);
	punkty.add_punkt(250, 150);
	punkty.add_punkt(300, 150);
	punkty.add_punkt(350, 150);
	punkty.add_punkt(400, 150);
	punkty.add_punkt(450, 150);
	punkty.add_punkt(500, 150);
	punkty.add_punkt(550, 150);
	punkty.add_punkt(620, 150);
	punkty.add_punkt(690, 150);
	punkty.add_punkt(790, 150);
	punkty.add_punkt(840, 150);
	punkty.add_punkt(890, 150);
	punkty.add_punkt(940, 150);
	punkty.add_punkt(990, 150);
	punkty.add_punkt(1040, 150);
	punkty.add_punkt(1090, 150);
	punkty.add_punkt(1190, 150);

	//4 wiersz
	punkty.add_punkt(50, 200);
	punkty.add_punkt(150, 200);
	punkty.add_punkt(250, 200);
	punkty.add_punkt(350, 200);
	punkty.add_punkt(450, 200);
	punkty.add_punkt(550, 200);
	punkty.add_punkt(690, 200);
	punkty.add_punkt(790, 200);
	punkty.add_punkt(890, 200);
	punkty.add_punkt(1090, 200);
	punkty.add_punkt(1190, 200);
	
	//5 wiersz
	punkty.add_punkt(50, 250);
	punkty.add_punkt(100, 250);
	punkty.add_punkt(150, 250);
	punkty.add_punkt(250, 250);
	punkty.add_punkt(350, 250);
	punkty.add_punkt(400, 250);
	punkty.add_punkt(450, 250);
	punkty.add_punkt(550, 250);
	punkty.add_punkt(690, 250);
	punkty.add_punkt(740, 250);
	punkty.add_punkt(790, 250);
	punkty.add_punkt(840, 250);
	punkty.add_punkt(890, 250);
	punkty.add_punkt(940, 250);
	punkty.add_punkt(990, 250);
	punkty.add_punkt(1090, 250);
	punkty.add_punkt(1140, 250);
	punkty.add_punkt(1190, 250);

	//6 wiersz
	punkty.add_punkt(250, 300);
	punkty.add_punkt(350, 300);
	punkty.add_punkt(550, 300);
	punkty.add_punkt(620, 300);
	punkty.add_punkt(690, 300);
	punkty.add_punkt(790, 300);
	punkty.add_punkt(990, 300);
	punkty.add_punkt(1190, 300);

	//7wiersz
	punkty.add_punkt(50, 350);
	punkty.add_punkt(100, 350);
	punkty.add_punkt(150, 350);
	punkty.add_punkt(200, 350);
	punkty.add_punkt(250, 350);
	punkty.add_punkt(350, 350);
	punkty.add_punkt(400, 350);
	punkty.add_punkt(450, 350);
	punkty.add_punkt(550, 350);
	punkty.add_punkt(690, 350);
	punkty.add_punkt(790, 350);
	punkty.add_punkt(840, 350);
	punkty.add_punkt(890, 350);
	punkty.add_punkt(990, 350);
	punkty.add_punkt(1040, 350);
	punkty.add_punkt(1090, 350);
	punkty.add_punkt(1140, 350);
	punkty.add_punkt(1190, 350);

	//8 wiersz
	punkty.add_punkt(50, 400);
	punkty.add_punkt(250, 400);
	punkty.add_punkt(450, 400);
	punkty.add_punkt(550, 400);
	punkty.add_punkt(620, 400);
	punkty.add_punkt(690, 400);
	punkty.add_punkt(890, 400);
	punkty.add_punkt(990, 400);
	
	//9 wiersz
	punkty.add_punkt(50, 450);
	punkty.add_punkt(100, 450);
	punkty.add_punkt(150, 450);
	punkty.add_punkt(250, 450);
	punkty.add_punkt(300, 450);
	punkty.add_punkt(350, 450);
	punkty.add_punkt(400, 450);
	punkty.add_punkt(450, 450);
	punkty.add_punkt(500, 450);
	punkty.add_punkt(550, 450);
	punkty.add_punkt(690, 450);
	punkty.add_punkt(790, 450);
	punkty.add_punkt(840, 450);
	punkty.add_punkt(890, 450);
	punkty.add_punkt(990, 450);
	punkty.add_punkt(1090, 450);
	punkty.add_punkt(1140, 450);
	punkty.add_punkt(1190, 450);
	//10 wiersz
	punkty.add_punkt(50, 500);
	punkty.add_punkt(150, 500);
	punkty.add_punkt(350, 500);
	punkty.add_punkt(450, 500);
	punkty.add_punkt(550, 500);
	punkty.add_punkt(690, 500);
	punkty.add_punkt(790, 500);
	punkty.add_punkt(890, 500);
	punkty.add_punkt(990, 500);
	punkty.add_punkt(1090, 500);
	punkty.add_punkt(1190, 500);
	
	//11 wiersz
	punkty.add_punkt(50, 550);
	punkty.add_punkt(150, 550);
	punkty.add_punkt(200, 550);
	punkty.add_punkt(250, 550);
	punkty.add_punkt(300, 550);
	punkty.add_punkt(350, 550);
	punkty.add_punkt(400, 550);
	punkty.add_punkt(450, 550);
	punkty.add_punkt(550, 550);
	punkty.add_punkt(620, 550);
	punkty.add_punkt(690, 550);
	punkty.add_punkt(740, 550);
	punkty.add_punkt(790, 550);
	punkty.add_punkt(840, 550);
	punkty.add_punkt(890, 550);
	punkty.add_punkt(940, 550);
	punkty.add_punkt(990, 550);
	punkty.add_punkt(1040, 550);
	punkty.add_punkt(1090, 550);
	punkty.add_punkt(1190, 550);

	//12wiersz
	punkty.add_punkt(50, 600);
	punkty.add_punkt(250, 600);
	punkty.add_punkt(350, 600);
	punkty.add_punkt(550, 600);
	punkty.add_punkt(690, 600);
	punkty.add_punkt(890, 600);
	punkty.add_punkt(990, 600);
	punkty.add_punkt(1190, 600);

	//13 wiersz
	punkty.add_punkt(100, 650);
	punkty.add_punkt(150, 650);
	punkty.add_punkt(200, 650);
	punkty.add_punkt(250, 650);
	punkty.add_punkt(350, 650);
	punkty.add_punkt(400, 650);
	punkty.add_punkt(450, 650);
	punkty.add_punkt(500, 650);
	punkty.add_punkt(550, 650);
	punkty.add_punkt(690, 650);
	punkty.add_punkt(740, 650);
	punkty.add_punkt(790, 650);
	punkty.add_punkt(840, 650);
	punkty.add_punkt(890, 650);
	punkty.add_punkt(990, 650);
	punkty.add_punkt(1040, 650);
	punkty.add_punkt(1090, 650);
	punkty.add_punkt(1140, 650);
	punkty.add_punkt(1190, 650);

	vector<Vector2f> ghostStartingPositions = {
		{40, 40},{1180, 40},{40, 640},{1180, 640},{40, 40}
	};
	/*GamePoints points(labirynth, ghostStartingPositions);*/


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		// Ruch PacMana
		p.move();
		p.handle_collision_with_wall(labirynth); 
		if (punkty.check_collision(p.get_bounding_box())) {
			punkty.remove_punkt(p.get_bounding_box()); // Usuwamy punkty, które pacman zje
		}
		/*points.checkCollisionWithPacman(p);*/

	
		// Ruch duszków z uwzglêdnieniem kolizji z labiryntem
		for (const auto& wall : labirynth.get_walls()) {
			if (wall.check_collision(g.get_bounding_box())) g.change_direction();
			if (wall.check_collision(g1.get_bounding_box())) g1.change_direction();
			if (wall.check_collision(g2.get_bounding_box())) g2.change_direction();
			if (wall.check_collision(g3.get_bounding_box())) g3.change_direction();
			if (wall.check_collision(g4.get_bounding_box())) g4.change_direction();
		}

		g.move(p, wall(0, 0, 0, 0));  // Duszki u¿ywaj¹ swojej logiki
		g1.move(p, wall(0, 0, 0, 0)); // U¿ycie pustego walla, bo logika jest w g³ównym
		g2.move(p, wall(0, 0, 0, 0));
		g3.move(p, wall(0, 0, 0, 0));
		g4.move(p, wall(0, 0, 0, 0));

		// Rysowanie
		window.clear();
		labirynth.draw(window);
		punkty.draw(window);
		/*points.draw(window);*/
		g.draw(window);
		g1.draw(window);
		g2.draw(window);
		g3.draw(window);
		g4.draw(window);
		p.draw(window);
		window.display();
	}

	return 0;
}

void map1(Labirynth& l)
{
	//ramki
	l.add_wall(0, 0, 1260, 30); // Œciana pozioma gorna
	l.add_wall(0, 30, 30, 660); // Œciana pionowa lewa
	l.add_wall(0, 690, 1260, 30); // Œciana pozioma dolna
	l.add_wall(1230, 30, 30, 660); // Œciana pionowa prawa

	//4 rogi
	//lewy gora
	l.add_wall(110, 110, 30, 200); //pionowa
	l.add_wall(140, 110, 80, 30); //pozioma
	//lewy dol
	l.add_wall(110, 410, 30, 200);//pionowa
	l.add_wall(140, 580, 80, 30);//pozioma
	//prawy gora
	l.add_wall(1120, 110, 30, 200);//pionowa
	l.add_wall(1040, 110, 80, 30);//pozioma

	//prawy dol
	l.add_wall(1120, 410, 30, 200); //pionowa
	l.add_wall(1040, 580, 80, 30); //pozioma


	//4 bolce pionowe
	l.add_wall(300, 30, 30, 110); //lewy gora
	l.add_wall(930, 30, 30, 110); //prawy gora
	l.add_wall(300, 580, 30, 110); //lewy dol
	l.add_wall(930, 580, 30, 110); //prawy dol

	//6 bolce poziome
	l.add_wall(220, 230, 110, 30); //lewy gorny
	l.add_wall(220, 345, 190, 30); //lewy srodek
	l.add_wall(220, 460, 110, 30); //lewy dol
	l.add_wall(930, 230, 110, 30); //prawy gora
	l.add_wall(850, 345, 190, 30); //prawy srodek
	l.add_wall(930, 460, 110, 30); //prawy dol

	//2 dlugie pionowe
	l.add_wall(410, 230, 30, 260);//lewy
	l.add_wall(820, 230, 30, 260);//prawy

	//2 dlugie poziome
	l.add_wall(410, 110, 440, 30);//gorny
	l.add_wall(410, 580, 440, 30);//dolny

	//srodek
	l.add_wall(520, 140, 30, 170);//pionowy gorny
	l.add_wall(520, 410, 30, 170);//pionowy dolny
	l.add_wall(630, 230, 30, 260);//pionowy srodek
	l.add_wall(660, 230, 80, 30);//poziomy gora
	l.add_wall(660, 345, 80, 30);//poziomy srodek
	l.add_wall(660, 460, 80, 30);//poziomy dol
}

void map2(Labirynth& l)
{	//ramki
	l.add_wall(0, 0, 1260, 20); // Œciana pozioma gorna
	l.add_wall(0, 20, 20, 680); // Œciana pionowa lewa
	l.add_wall(0, 700, 1260, 20); // Œciana pozioma dolna
	l.add_wall(1240, 20, 20, 680); // Œciana pionowa prawa
	///lewa strona
	l.add_wall(100, 600, 120, 20);//poziomy
	l.add_wall(100, 520, 20, 80);//pionowy

	l.add_wall(300, 600, 20, 100);//pionowy

	l.add_wall(400, 600, 100, 20);//poziomy
	l.add_wall(500, 500, 20, 120);//pionowy
	l.add_wall(400, 500, 20, 20);//kwadrat

	l.add_wall(200, 500, 120, 20);//poziomy cienki
	l.add_wall(200, 400, 20, 100);//pionowy 
	l.add_wall(100, 400, 100, 40);//poziomy gruby

	l.add_wall(300, 400, 120, 20);//poziomy lewy
	l.add_wall(300, 200, 20, 200);//pionowy lewy
	l.add_wall(500, 200, 20, 220);//pionowy prawy
	l.add_wall(400, 300, 100, 20);//poziomy prawy
	l.add_wall(400, 200, 20, 20);//kwadrat

	l.add_wall(20, 280, 200, 40);//gruby poziomy
	l.add_wall(200, 200, 20, 80);//pionowy dolny
	l.add_wall(100, 100, 20, 100);//pionowy gorny
	l.add_wall(120, 100, 100, 20);//poziomy gorny

	l.add_wall(300, 20, 20, 100);//pionowy samotnik
	l.add_wall(400, 100, 120, 20);//poziomy samotnik

	//srodek
	l.add_wall(600, 20, 60, 100);//gorny prostokat
	l.add_wall(600, 200, 60, 60);//gorny kwadrat
	l.add_wall(600, 340, 60, 40);//srodkowy
	l.add_wall(600, 460, 60, 60);//dolny kwadrat
	l.add_wall(600, 600, 60, 100);//dolny prostokat


	//prawa strona
	l.add_wall(740, 100, 120, 20);//poziomy lewy
	l.add_wall(740, 120, 20, 100);//pionowy lewy
	l.add_wall(840, 200, 20, 20);//kwadrat

	l.add_wall(940, 20, 20, 100);//pionowy samotny
	l.add_wall(1040, 100, 120, 20);//poziomy rog
	l.add_wall(1140, 120, 20, 80);//pionowy rog

	l.add_wall(940, 200, 120, 20);//poziomy
	l.add_wall(1040, 220, 20, 100);//pionowy cienki
	l.add_wall(1060, 280, 100, 40);//poziomy gruby

	l.add_wall(740, 300, 20, 220);//pionowy
	l.add_wall(760, 400, 100, 20);//poziomy
	l.add_wall(840, 300, 120, 20);//pionowy
	l.add_wall(940, 320, 20, 200);//poziomy
	l.add_wall(840, 500, 20, 20);//kwadrat

	l.add_wall(1040, 400, 200, 40);//gruby ze sciany
	l.add_wall(1040, 440, 20, 80);//pionowy

	l.add_wall(740, 600, 120, 20);//poziomy samotnik
	l.add_wall(940, 600, 20, 100);//pionowy samotnik
	l.add_wall(1040, 600, 120, 20);//poziomy
	l.add_wall(1140, 520, 20, 80);
}
void map3(Labirynth& l)
{
	//ramki
	l.add_wall(0, 0, 1260, 10); // Œciana pozioma gorna
	l.add_wall(0, 10, 10, 700); // Œciana pionowa lewa
	l.add_wall(0, 710, 1260, 10); // Œciana pozioma dolna
	l.add_wall(1250, 10, 10, 700); // Œciana pionowa prawa

	//lewy rog
	l.add_wall(10, 510, 80, 20);//maly bolec ze sciany poziomy
	l.add_wall(270, 410, 100, 20);//samotny poziomy

	//niepelnosprawne f
	l.add_wall(90, 610, 280, 20);//poziomy z f
	l.add_wall(270, 510, 20, 100);//pionowy z f

	//odwrocona elka
	l.add_wall(170, 410, 20, 120);//pionowy z odwroconej elki
	l.add_wall(90, 410, 80, 20);//poziomy z odwroconej elki

	//kinole
	l.add_wall(370, 510, 180, 20);//kinol dolny poziome
	l.add_wall(450, 530, 20, 100);//kinol dolny pionowe

	l.add_wall(450, 330, 20, 100);//kinol pionowe gorne
	l.add_wall(370, 310, 180, 20);//kinol poziome gora

	l.add_wall(370, 90, 180, 20);//kinol najwyzszy poziome
	l.add_wall(450, 110, 20, 120);//kinol najwyzszy pionowe

	//prawy rog
	l.add_wall(910, 610, 85, 20); // poziomy dol 1
	l.add_wall(1075, 610, 85, 20);//poziomy dol 2
	l.add_wall(830, 510, 330, 20);//poziomy gora
	l.add_wall(910, 410, 20, 100);//pionowy gora
	l.add_wall(550, 410, 100, 20);
	l.add_wall(1000, 410, 160, 20);
	//niepelnosprawne f
	l.add_wall(550, 610, 280, 20);//poziomy z f
	l.add_wall(630, 510, 20, 100);//pionowy z f



	//odwr elka
	l.add_wall(730, 410, 20, 120);//pionowy z elki
	l.add_wall(750, 410, 80, 20);//poziomy z elki

	//srodek
	l.add_wall(270, 230, 20, 100);//pionowy lewy
	l.add_wall(270, 210, 100, 20);//poziomy lewy
	l.add_wall(630, 230, 20, 100);//pionowy prawy
	l.add_wall(550, 210, 100, 20);//poziomy prawy


	//lewy gora
	l.add_wall(90, 90, 20, 240);//pionowy
	l.add_wall(110, 210, 80, 20);//poziomy
	l.add_wall(190, 10, 20, 80);//pionowy lewy gora
	l.add_wall(190, 90, 100, 20);//poziomy lewy gora

	//prawy gora
	l.add_wall(630, 90, 100, 20);//poziomy prawy gora
	l.add_wall(710, 10, 20, 80);//pionowy prawy gora
	l.add_wall(730, 210, 80, 20);//poziomy
	l.add_wall(810, 90, 20, 240);//pionowy
	//kwadrat duzy
	l.add_wall(890, 90, 20, 240);//lewy bok
	l.add_wall(910, 90, 260, 20);//gora
	l.add_wall(1150, 90, 20, 240);//prawy bok
	l.add_wall(910, 310, 80, 20);//lewy dol
	l.add_wall(1070, 310, 100, 20);//prawy dol
	l.add_wall(980, 170, 100, 80);
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
//	// Rysuje wszystkie œciany w labiryncie
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
//				break; // Tylko jedna kolizja jest mo¿liwa na raz
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
//	bool isBlocked;  // Flaga informuj¹ca, czy duszek jest zablokowany przez œcianê
//
//public:
//	ghost(const int x, const int y, const Color color)
//	{
//		p.x = x;
//		p.y = y;
//		color1 = color;
//		currentDirection = { false, true, false, false }; // Domyœlny kierunek: w prawo
//		isBlocked = false;  // Pocz¹tkowo duszek nie jest zablokowany
//	}
//
//	// Funkcja zmieniaj¹ca kierunek o 90 stopni zgodnie z ruchem wskazówek zegara
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
//	// Funkcja sprawdzaj¹ca, czy duszek ma zbli¿yæ siê do PacMana
//	void move_towards_pacman(const pacman& pacman, const Labirynth& labirynth)
//	{
//		// Obliczanie ró¿nicy pozycji w obu osiach
//		float dx = pacman.get_position().x - p.x;
//		float dy = pacman.get_position().y - p.y;
//
//		// Normalizacja wektora kierunku
//		float distance = sqrt(dx * dx + dy * dy); // Odleg³oœæ do PacMana
//		dx /= distance;
//		dy /= distance;
//
//		// Zmiana kierunku na podstawie PacMana
//		if (abs(dx) > abs(dy)) { // Je¿eli ruch w osi X jest wiêkszy
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
//		else { // Je¿eli ruch w osi Y jest wiêkszy
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
//			p.y -= SPEED / 2.0; // Ruch w górê
//		}
//		else if (currentDirection.down && !wall_collision_down(labirynth)) {
//			p.y += SPEED / 2.0; // Ruch w dó³
//		}
//		else {
//			// Jeœli napotka œcianê w wybranym kierunku, spróbuj innego
//			if (currentDirection.left && wall_collision_left(labirynth)) {
//				// SprawdŸ inne kierunki
//				if (!wall_collision_up(labirynth)) {
//					p.y -= SPEED / 2.0; // Ruch w górê
//				}
//				else if (!wall_collision_down(labirynth)) {
//					p.y += SPEED / 2.0; // Ruch w dó³
//				}
//				else if (!wall_collision_right(labirynth)) {
//					p.x += SPEED / 2.0; // Ruch w prawo
//				}
//			}
//			else if (currentDirection.right && wall_collision_right(labirynth)) {
//				// SprawdŸ inne kierunki
//				if (!wall_collision_up(labirynth)) {
//					p.y -= SPEED / 2.0; // Ruch w górê
//				}
//				else if (!wall_collision_down(labirynth)) {
//					p.y += SPEED / 2.0; // Ruch w dó³
//				}
//				else if (!wall_collision_left(labirynth)) {
//					p.x -= SPEED / 2.0; // Ruch w lewo
//				}
//			}
//			else if (currentDirection.up && wall_collision_up(labirynth)) {
//				// SprawdŸ inne kierunki
//				if (!wall_collision_left(labirynth)) {
//					p.x -= SPEED / 2.0; // Ruch w lewo
//				}
//				else if (!wall_collision_right(labirynth)) {
//					p.x += SPEED / 2.0; // Ruch w prawo
//				}
//				else if (!wall_collision_down(labirynth)) {
//					p.y += SPEED / 2.0; // Ruch w dó³
//				}
//			}
//			else if (currentDirection.down && wall_collision_down(labirynth)) {
//				// SprawdŸ inne kierunki
//				if (!wall_collision_left(labirynth)) {
//					p.x -= SPEED / 2.0; // Ruch w lewo
//				}
//				else if (!wall_collision_right(labirynth)) {
//					p.x += SPEED / 2.0; // Ruch w prawo
//				}
//				else if (!wall_collision_up(labirynth)) {
//					p.y -= SPEED / 2.0; // Ruch w górê
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
//	// Sprawdzanie kolizji w górê
//	bool wall_collision_up(const Labirynth& labirynth) {
//		FloatRect ghostBounds = get_bounding_box();
//		ghostBounds.top -= SPEED / 2.0;
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(ghostBounds)) return true;
//		}
//		return false;
//	}
//
//	// Sprawdzanie kolizji w dó³
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
//		// Generowanie punktów w siatce 40x40
//		for (float y = 0; y < HEIGHT; y += 40.5) {
//			for (float x = 0; x < WIDTH; x += 40.5) {
//				FloatRect pointBounds(x + 10, y + 10, 20, 20); // Obszar punktu
//
//				// SprawdŸ, czy punkt nie koliduje ze œcianami
//				bool collidesWithWall = false;
//				for (const auto& wall : labirynth.get_walls()) {
//					if (wall.check_collision(pointBounds)) {
//						collidesWithWall = true;
//						break;
//					}
//				}
//
//				// SprawdŸ, czy punkt nie jest w strefie startowej duszków
//
//
//				if (!collidesWithWall) {
//					CircleShape point(10); // Promieñ 10 = œrednica 20
//					point.setFillColor(Color::White);
//					point.setPosition(x, y);
//					points.push_back(point);
//				}
//			}
//		}
//	}
//
//	void checkCollisionWithPacman(const pacman& p) {
//		FloatRect pacmanBounds(p.get_position().x, p.get_position().y, 30, 30); // PacMan ma œrednicê 40
//
//		for (auto it = points.begin(); it != points.end();) {
//			if (it->getGlobalBounds().intersects(pacmanBounds)) {
//				it = points.erase(it); // Usuñ punkt
//				score++; // Zwiêksz liczbê punktów
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
//		// Rysowanie licznika punktów
//		Font font;
//		if (!font.loadFromFile("arial.ttf")) {
//			cerr << "Nie mo¿na za³adowaæ czcionki!\n";
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
//		// Ruch duszków z uwzglêdnieniem kolizji z labiryntem
//		for (const auto& wall : labirynth.get_walls()) {
//			if (wall.check_collision(g.get_bounding_box())) g.change_direction();
//			if (wall.check_collision(g1.get_bounding_box())) g1.change_direction();
//			if (wall.check_collision(g2.get_bounding_box())) g2.change_direction();
//			if (wall.check_collision(g3.get_bounding_box())) g3.change_direction();
//			if (wall.check_collision(g4.get_bounding_box())) g4.change_direction();
//		}
//
//		g.move_towards_pacman(p, labirynth);  // Duszki u¿ywaj¹ swojej logiki
//		g1.move_towards_pacman(p, labirynth); // U¿ycie pustego walla, bo logika jest w g³ównym
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
//	l.add_wall(0, 0, 760, 40); // Œciana pozioma gorna
//	l.add_wall(0, 40, 40, 800); // Œciana pionowa lewa
//	l.add_wall(0, 840, 760, 40); // Œciana pozioma dolna
//	l.add_wall(720, 40, 40, 800); // Œciana pionowa prawa
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