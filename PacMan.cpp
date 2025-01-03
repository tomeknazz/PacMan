




//dzialajacy labirynt 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<windows.h>
#include<iostream>
#include <cstdlib> // Include for rand()

constexpr double SPEED = 0.05;
constexpr int WIDTH = 1260;
constexpr int HEIGHT = 720;
using namespace std;
using namespace sf;





class Wall {
public:
	RectangleShape shape;

	Wall(float x, float y, float width = 100.f, float height = 40.f) {
		shape.setSize(Vector2f(width, height));
		shape.setFillColor(Color::Blue);
		shape.setPosition(x, y);
	}

	bool checkCollision(const FloatRect& boundingBox) const {
		return shape.getGlobalBounds().intersects(boundingBox);
	}

	void draw(RenderWindow& window) const {
		window.draw(shape);
	}
};

class Labirynth {
private:
	std::vector<Wall> walls;

public:
	Labirynth() {}

	// Dodaje œcianê do labiryntu
	void addWall(float x, float y, float width, float height) {
		walls.emplace_back(x, y, width, height);
	}

	// Sprawdza kolizjê z dowoln¹ œcian¹ w labiryncie
	bool checkCollision(const FloatRect& boundingBox) const {
		for (const auto& wall : walls) {
			if (wall.checkCollision(boundingBox)) {
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

	const std::vector<Wall>& getWalls() const {
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
	movement m;
	pacman()
	{
		movement m;
		p.x = 300;
		p.y = 300;
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
	void handleCollisionWithWall(const Labirynth& labirynth) {
		for (const auto& wall : labirynth.getWalls()) {
			if (wall.checkCollision(getBoundingBox())) {
				// Cofnij ruch w przypadku kolizji
				if (m.left) p.x += speed;
				if (m.right) p.x -= speed;
				if (m.up) p.y += speed;
				if (m.down) p.y -= speed;

				break; // Tylko jedna kolizja jest mo¿liwa na raz
			}
		}
	}
	FloatRect getBoundingBox() const {
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
	movement m;
	ghost(const int x, const int y, Color color)
	{
		p.x = x;
		p.y = y;
		color1 = color;
	}
	void changeDirection() {
		// Losowa zmiana kierunku o 90 stopni
		int direction = rand() % 4;
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

	FloatRect getBoundingBox() const {
		CircleShape shape(20.f);
		shape.setPosition(p.x, p.y);
		return shape.getGlobalBounds();
	}

	void move(const pacman pacman, const Wall& wall)
	{
		if (wall.checkCollision(getBoundingBox())) {
			changeDirection(); // Zmiana kierunku po kolizji
		}
		if (static_cast<int>(floor(sqrt(pow(pacman.get_position().x, 2) + pow(pacman.get_position().y, 2)))) % 100 == 0) {
			float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Generate a random float between 0 and 1
			if (r < 0.25) {
				m.down = true;
				m.left = false;
				m.right = false;
				m.up = false;
			}
			else if (r < 0.5 && r >= 0.25)
			{
				m.left = true;
				m.down = false;
				m.right = false;
				m.up = false;
			}
			else if (r < 0.75 && r >= 0.5)
			{
				m.right = true;
				m.down = false;
				m.left = false;
				m.up = false;
			}
			else
			{
				m.up = true;
				m.down = false;
				m.left = false;
				m.right = false;
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


int main() {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");
	pacman p;
	ghost g(40, 40, Color::Green);
	ghost g1(1180, 40, Color::Red);
	ghost g2(40, 640, Color::Cyan);
	ghost g3(1180, 640, Color::White);
	ghost g4(570, 400, Color::Magenta);

	// Tworzenie labiryntu
	Labirynth labirynth;
	
	//ramki
	labirynth.addWall(0, 0, 1260, 30); // Œciana pozioma gorna
	labirynth.addWall(0, 30, 30, 660); // Œciana pionowa lewa
	labirynth.addWall(0, 690, 1260, 30); // Œciana pozioma dolna
	labirynth.addWall(1230, 30, 30, 660); // Œciana pionowa prawa

	//Mapa 1
	
	//4 rogi
	//lewy gora
	labirynth.addWall(110, 110, 30, 200); //pionowa
	labirynth.addWall(140, 110, 80, 30); //pozioma
	//lewy dol
	labirynth.addWall(110, 410, 30, 200);//pionowa
	labirynth.addWall(140, 580, 80, 30);//pozioma
	//prawy gora
	labirynth.addWall(1120, 110, 30, 200);//pionowa
	labirynth.addWall(1040, 110, 80, 30);//pozioma
	
	//prawy dol
	labirynth.addWall(1120, 410, 30, 200); //pionowa
	labirynth.addWall(1040, 580, 80, 30); //pozioma
	

	//4 bolce pionowe
	labirynth.addWall(300, 30, 30, 110); //lewy gora
	labirynth.addWall(930, 30, 30, 110); //prawy gora
	labirynth.addWall(300, 580, 30, 110); //lewy dol
	labirynth.addWall(930, 580, 30, 110); //prawy dol

	//6 bolce poziome
	labirynth.addWall(220, 230, 110, 30); //lewy gorny
	labirynth.addWall(220, 345, 190, 30); //lewy srodek
	labirynth.addWall(220, 460, 110, 30); //lewy dol
	labirynth.addWall(930, 230, 110, 30); //prawy gora
	labirynth.addWall(850, 345, 190, 30); //prawy srodek
	labirynth.addWall(930, 460, 110, 30); //prawy dol

	//2 dlugie pionowe
	labirynth.addWall(410, 230, 30, 260);//lewy
	labirynth.addWall(820,230,30,260);//prawy

	//2 dlugie poziome
	labirynth.addWall(410, 110, 440, 30);//gorny
	labirynth.addWall(410,580,440,30);//dolny

	//srodek
	labirynth.addWall(520, 140, 30, 170);//pionowy gorny
	labirynth.addWall(520, 410, 30, 170);//pionowy dolny
	labirynth.addWall(630, 230, 30, 260);//pionowy srodek
	labirynth.addWall(660, 230, 80, 30);//poziomy gora
	labirynth.addWall(660, 345, 80, 30);//poziomy srodek
	labirynth.addWall(660, 460, 80, 30);//poziomy dol
	


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		// Ruch PacMana
		p.move();
		p.handleCollisionWithWall(labirynth);

		// Ruch duszków z uwzglêdnieniem kolizji z labiryntem
		for (const auto& wall : labirynth.getWalls()) {
			if (wall.checkCollision(g.getBoundingBox())) g.changeDirection();
			if (wall.checkCollision(g1.getBoundingBox())) g1.changeDirection();
			if (wall.checkCollision(g2.getBoundingBox())) g2.changeDirection();
			if (wall.checkCollision(g3.getBoundingBox())) g3.changeDirection();
			if (wall.checkCollision(g4.getBoundingBox())) g4.changeDirection();
		}

		g.move(p, Wall(0, 0, 0, 0));  // Duszki u¿ywaj¹ swojej logiki
		g1.move(p, Wall(0, 0, 0, 0)); // U¿ycie pustego walla, bo logika jest w g³ównym
		g2.move(p, Wall(0, 0, 0, 0));
		g3.move(p, Wall(0, 0, 0, 0));
		g4.move(p, Wall(0, 0, 0, 0));

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

