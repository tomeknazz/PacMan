// PacMan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include<windows.h>
#include<iostream>
constexpr double SPEED = 0.09;
class pacman
{
private:
	double x;
	double y;
	double speed;

	struct movement
	{
		bool left;
		bool right;
		bool up;
		bool down;
	};
public:
	pacman()
	{
		x = 0;
		y = 0;
		speed = SPEED;
	}
	void move()
	{
		movement m;
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

		if (m.left)
		{
			x -= speed;
		}
		if (m.right)
		{
			x += speed;
		}
		if (m.up)
		{
			y -= speed;
		}
		if (m.down)
		{
			y += speed;
		}
	}
	void draw(sf::RenderWindow& window) const
	{
		sf::CircleShape shape(20.f);
		shape.setFillColor(sf::Color::Yellow);
		shape.setPosition(x, y);
		window.draw(shape);
	}
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(1260, 720), "PacMan");
	pacman p;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		p.move();

		window.clear();
		p.draw(window);
		window.display();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
