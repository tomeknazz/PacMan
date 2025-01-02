#include <SFML/Graphics.hpp>
#include<windows.h>
#include<iostream>
#include <cstdlib> // Include for rand()

constexpr double SPEED = 0.09;
constexpr int WIDTH = 1260;
constexpr int HEIGHT = 720;
using namespace std;
using namespace sf;
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

	void move(const pacman pacman)
	{
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
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		p.move();
		g.move(p);
		g1.move(p);
		g2.move(p);
		window.clear();
		g1.draw(window);
		g2.draw(window);
		g.draw(window);
		p.draw(window);
		window.display();
	}

	return 0;
}
