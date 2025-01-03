#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<windows.h>
#include<iostream>
#include <cstdlib> // Include for rand()

constexpr double SPEED = 0.09;
constexpr int WIDTH = 1260;
constexpr int HEIGHT = 720;
using namespace std;
using namespace sf;



 class Wall {
	public:
	    RectangleShape shape;
	
	    Wall(float x, float y) {
	        shape.setSize(Vector2f(600.f, 600.f)); // Œciana o rozmiarze 100x40
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
		p.x = 0;
		p.y = 0;
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

	void move(const pacman pacman,const Wall& wall)
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
		if (get_position().x <= 1) p.x += SPEED / 3.;
		if (get_position().x >= WIDTH - 41) p.x -= SPEED / 3.;
		if (get_position().y <= 1) p.y += SPEED / 3.;
		if (get_position().y >= HEIGHT - 41) p.y -= SPEED / 3.;
		if (m.left) p.x -= SPEED / 3.;
		if (m.right) p.x += SPEED / 3.;
		if (m.up) p.y -= SPEED / 3.;
		if (m.down) p.y += SPEED / 3.;
		
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


int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");
	pacman p;
	ghost g(630, 360, Color::Green);
	ghost g1(630, 360, Color::Red);
	ghost g2(630, 360, Color::Cyan);
	
	Wall wall(800, 300);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		p.move();
		g.move(p,wall);
		g1.move(p,wall);
		g2.move(p,wall);
		window.clear();
		wall.draw(window);
		g1.draw(window);
		g2.draw(window);
		g.draw(window);
		p.draw(window);
		window.display();
	}

	return 0;
}


//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <windows.h>
//#include <iostream>
//#include <cstdlib> // Include for rand()
//
//constexpr double SPEED = 0.09;
//constexpr int WIDTH = 1260;
//constexpr int HEIGHT = 720;
//
//using namespace std;
//using namespace sf;
//
//class Wall {
//public:
//    RectangleShape shape;
//
//    Wall(float x, float y) {
//        shape.setSize(Vector2f(100.f, 40.f)); // Œciana o rozmiarze 100x40
//        shape.setFillColor(Color::Blue);
//        shape.setPosition(x, y);
//    }
//
//    bool checkCollision(const FloatRect& boundingBox) const {
//        return shape.getGlobalBounds().intersects(boundingBox);
//    }
//
//    void draw(RenderWindow& window) const {
//        window.draw(shape);
//    }
//};
//
//class pacman {
//private:
//    struct position {
//        float x;
//        float y;
//    };
//
//    float speed;
//
//    struct movement {
//        bool left;
//        bool right;
//        bool up;
//        bool down;
//    };
//
//public:
//    position p;
//    movement m;
//
//    pacman() {
//        m.left = m.right = m.up = m.down = false;
//        p.x = 0;
//        p.y = 0;
//        speed = SPEED;
//    }
//
//    void move() {
//        if (GetAsyncKeyState(VK_LEFT)) {
//            m.left = true;
//            m.right = m.up = m.down = false;
//        }
//        if (GetAsyncKeyState(VK_RIGHT)) {
//            m.right = true;
//            m.left = m.up = m.down = false;
//        }
//        if (GetAsyncKeyState(VK_UP)) {
//            m.up = true;
//            m.left = m.right = m.down = false;
//        }
//        if (GetAsyncKeyState(VK_DOWN)) {
//            m.down = true;
//            m.left = m.right = m.up = false;
//        }
//
//        if (get_position().x <= 1) p.x += speed;
//        if (get_position().x >= WIDTH - 41) p.x -= speed;
//        if (get_position().y <= 1) p.y += speed;
//        if (get_position().y >= HEIGHT - 41) p.y -= speed;
//        if (m.left) p.x -= speed;
//        if (m.right) p.x += speed;
//        if (m.up) p.y -= speed;
//        if (m.down) p.y += speed;
//    }
//
//    void draw(RenderWindow& window) const {
//        CircleShape shape(20.f);
//        shape.setFillColor(Color::Yellow);
//        shape.setPosition(p.x, p.y);
//        window.draw(shape);
//    }
//
//    position get_position() const {
//        return p;
//    }
//
//    FloatRect getBoundingBox() const {
//        CircleShape shape(20.f);
//        shape.setPosition(p.x, p.y);
//        return shape.getGlobalBounds();
//    }
//};
//
//class ghost {
//private:
//    struct position {
//        float x;
//        float y;
//    };
//
//    struct movement {
//        bool left;
//        bool right;
//        bool up;
//        bool down;
//    };
//
//    Color color1;
//    movement m;
//
//public:
//    position p;
//
//    ghost(float x, float y, Color color) {
//        p.x = x;
//        p.y = y;
//        color1 = color;
//        m.left = m.right = m.up = m.down = false;
//        m.right = true; // Domyœlny kierunek ruchu
//    }
//
//    void move(const Wall& wall) {
//        // Sprawdzanie kolizji ze œcian¹
//        if (wall.checkCollision(getBoundingBox())) {
//            changeDirection(); // Zmiana kierunku po kolizji
//        }
//
//        // Ruch w aktualnym kierunku
//        if (m.left) p.x -= SPEED / 3.;
//        if (m.right) p.x += SPEED / 3.;
//        if (m.up) p.y -= SPEED / 3.;
//        if (m.down) p.y += SPEED / 3.;
//
//        // Ograniczenie w oknie
//        if (p.x <= 0) {
//            m.left = false;
//            m.right = true;
//        }
//        if (p.x >= WIDTH - 40) {
//            m.right = false;
//            m.left = true;
//        }
//        if (p.y <= 0) {
//            m.up = false;
//            m.down = true;
//        }
//        if (p.y >= HEIGHT - 40) {
//            m.down = false;
//            m.up = true;
//        }
//    }
//
//    void changeDirection() {
//        // Losowa zmiana kierunku o 90 stopni
//        int direction = rand() % 4;
//        if (direction == 0) {
//            m.left = true;
//            m.right = m.up = m.down = false;
//        }
//        else if (direction == 1) {
//            m.right = true;
//            m.left = m.up = m.down = false;
//        }
//        else if (direction == 2) {
//            m.up = true;
//            m.left = m.right = m.down = false;
//        }
//        else {
//            m.down = true;
//            m.left = m.right = m.up = false;
//        }
//    }
//
//    Color get_color() const {
//        return color1;
//    }
//
//    void draw(RenderWindow& window) const {
//        CircleShape shape(20.f);
//        shape.setFillColor(get_color());
//        shape.setPosition(p.x, p.y);
//        window.draw(shape);
//    }
//
//    FloatRect getBoundingBox() const {
//        CircleShape shape(20.f);
//        shape.setPosition(p.x, p.y);
//        return shape.getGlobalBounds();
//    }
//};
//
//int main() {
//    RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacMan");
//    pacman p;
//    ghost g(300, 300, Color::Green);
//    ghost g1(400, 300, Color::Red);
//    ghost g2(500, 300, Color::Cyan);
//
//    // Jedna œciana w œrodku okna
//    Wall wall(800,300 );
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        p.move();
//        g.move(wall);
//        g1.move(wall);
//        g2.move(wall);
//
//        window.clear();
//
//        // Rysowanie œciany
//        wall.draw(window);
//
//        // Rysowanie duszków i PacMana
//        g.draw(window);
//        g1.draw(window);
//        g2.draw(window);
//        p.draw(window);
//
//        window.display();
//    }
//
//    return 0;
//}