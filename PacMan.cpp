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
	void handle_collision_with_wall(const labirynth& labirynth) {
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
		CircleShape shape(20.f); // Rozmiar PacMana
		shape.setPosition(p.x, p.y);
		return shape.getGlobalBounds();
	}


	void draw(RenderWindow& window) const
	{
		CircleShape shape(20.f);
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
		CircleShape shape(20.f);
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
		CircleShape shape(20.f);
		shape.setFillColor(get_color());
		shape.setPosition(p.x, p.y);
		window.draw(shape);
	}
};

void map1(labirynth& l);
void map2(labirynth& l);
void map3(labirynth& l);

int main() {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");
	pacman p;
	ghost g(40, 40, Color::Green);
	ghost g1(1180, 40, Color::Red);
	ghost g2(40, 640, Color::Cyan);
	ghost g3(1180, 640, Color::White);
	ghost g4(40, 40, Color::Magenta);

	// Tworzenie labiryntu
	labirynth labirynth;

	/*map1(labirynth);*/
	map2(labirynth);
	/*map3(labirynth);*/
	

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		// Ruch PacMana
		p.move();
		p.handle_collision_with_wall(labirynth);

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
		labirynth.draw(window); // Rysowanie labiryntu
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

void map1(labirynth& l)
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
void map2(labirynth& l)
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
void map3(labirynth& l)
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
	l.add_wall(450,530,20,100);//kinol dolny pionowe

	l.add_wall(450,330,20,100);//kinol pionowe gorne
	l.add_wall(370,310,180,20);//kinol poziome gora

	l.add_wall(370, 90, 180, 20);//kinol najwyzszy poziome
	l.add_wall(450, 110, 20, 120);//kinol najwyzszy pionowe

	//prawy rog
	l.add_wall(910,610,85,20); // poziomy dol 1
	l.add_wall(1075, 610, 85, 20);//poziomy dol 2
	l.add_wall(830,510,330,20);//poziomy gora
	l.add_wall(910, 410, 20, 100);//pionowy gora
	l.add_wall(550, 410, 100, 20);
	l.add_wall(1000, 410, 160, 20);
	//niepelnosprawne f
	l.add_wall(550,610,280,20);//poziomy z f
	l.add_wall(630,510,20,100);//pionowy z f

	

	//odwr elka
	l.add_wall(730,410,20,120);//pionowy z elki
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