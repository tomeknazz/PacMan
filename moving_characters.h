#pragma once
#include <windows.h>
#undef min
#undef max
#include <SFML/Graphics.hpp>

#include "constants.h"
#include "map.h"

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
	Texture texture;

	pacman()
	{
		p.x = 550;
		p.y = 645;
		speed = SPEED;
	}

	pacman(const int x, const int y, const Texture& texture1)
	{
		p.x = x;
		p.y = y;
		speed = SPEED;
		texture = texture1;
	}

	void setTexture(const Texture& newTexture)
	{
		texture = newTexture;
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
		shape.setPosition(p.x, p.y);
		shape.setTexture(&texture); // Set the texture
		window.draw(shape);
	}

	position get_position() const
	{
		return p;
	}
};

class ghost : public pacman
{
private:;
	   struct movement
	   {
		   bool left;
		   bool right;
		   bool up;
		   bool down;
	   };
	   movement currentDirection;
	   bool isBlocked;  // Flaga informujaca, czy duszek jest zablokowany przez sciane

public:
	Texture texture2;
	ghost(const int x, const int y, const Texture& color)
	{
		p.x = x;
		p.y = y;
		texture2 = color;
		currentDirection = { false, true, false, false }; // Domyslny kierunek: w prawo
		isBlocked = false; // Poczatkowo duszek nie jest zablokowany
	}

	bool check_collision_with_pacman(const pacman& pacman) const {
		return get_bounding_box().intersects(pacman.get_bounding_box());
	}

	// Funkcja zmieniajaca kierunek o 90 stopni zgodnie z ruchem wskazowek zegara
	void change_direction() {
		if (currentDirection.left) {
			currentDirection.left = false;
			currentDirection.up = true;
			currentDirection.right = false;
			currentDirection.down = false;
		}
		else if (currentDirection.up) {
			currentDirection.left = false;
			currentDirection.up = false;
			currentDirection.right = true;
			currentDirection.down = false;
		}
		else if (currentDirection.right) {
			currentDirection.left = false;
			currentDirection.up = false;
			currentDirection.right = false;
			currentDirection.down = true;
		}
		else if (currentDirection.down) {
			currentDirection.left = true;
			currentDirection.up = false;
			currentDirection.right = false;
			currentDirection.down = false;
		}
	}

	// Funkcja sprawdzajaca, czy duszek ma zblizyæ sie do PacMana
	void move_towards_pacman(const pacman& pacman, const labirynth& labirynth)
	{
		// Obliczanie roznicy pozycji w obu osiach
		float dx = pacman.get_position().x - p.x;
		float dy = pacman.get_position().y - p.y;

		// Normalizacja wektora kierunku
		float distance = sqrt(dx * dx + dy * dy); // Odleglosæ do PacMana
		dx /= distance;
		dy /= distance;

		// Zmiana kierunku na podstawie PacMana
		if (abs(dx) > abs(dy)) { // Jezeli ruch w osi X jest wiekszy
			if (dx > 0) {
				currentDirection.left = false;
				currentDirection.right = true;
			}
			else {
				currentDirection.left = true;
				currentDirection.right = false;
			}
			currentDirection.up = false;
			currentDirection.down = false;
		}
		else { // Jezeli ruch w osi Y jest wiekszy
			if (dy > 0) {
				currentDirection.down = true;
				currentDirection.up = false;
			}
			else {
				currentDirection.up = true;
				currentDirection.down = false;
			}
			currentDirection.left = false;
			currentDirection.right = false;
		}

		// Sprawdzanie kolizji w wybranym kierunku
		if (currentDirection.left && !wall_collision_left(labirynth)) {
			p.x -= SPEED / 2.0; // Ruch w lewo
		}

		else if (currentDirection.right && !wall_collision_right(labirynth)) {
			p.x += SPEED / 2.0; // Ruch w prawo
		}
		else if (currentDirection.up && !wall_collision_up(labirynth)) {
			p.y -= SPEED / 2.0; // Ruch w gore
		}
		else if (currentDirection.down && !wall_collision_down(labirynth)) {
			p.y += SPEED / 2.0; // Ruch w dol
		}
		else {
			// Jesli napotka sciane w wybranym kierunku, sprobuj innego
			if (currentDirection.left && wall_collision_left(labirynth)) {
				// Sprawd inne kierunki
				if (!wall_collision_up(labirynth)) {
					p.y -= SPEED / 2.0; // Ruch w gore
				}
				else if (!wall_collision_down(labirynth)) {
					p.y += SPEED / 2.0; // Ruch w dol
				}
				else if (!wall_collision_right(labirynth)) {
					p.x += SPEED / 2.0; // Ruch w prawo
				}
			}
			else if (currentDirection.right && wall_collision_right(labirynth)) {
				// Sprawd inne kierunki
				if (!wall_collision_up(labirynth)) {
					p.y -= SPEED / 2.0; // Ruch w gore
				}
				else if (!wall_collision_down(labirynth)) {
					p.y += SPEED / 2.0; // Ruch w dol
				}
				else if (!wall_collision_left(labirynth)) {
					p.x -= SPEED / 2.0; // Ruch w lewo
				}
			}
			else if (currentDirection.up && wall_collision_up(labirynth)) {
				// Sprawd inne kierunki
				if (!wall_collision_left(labirynth)) {
					p.x -= SPEED / 2.0; // Ruch w lewo
				}
				else if (!wall_collision_right(labirynth)) {
					p.x += SPEED / 2.0; // Ruch w prawo
				}
				else if (!wall_collision_down(labirynth)) {
					p.y += SPEED / 2.0; // Ruch w dol
				}
			}
			else if (currentDirection.down && wall_collision_down(labirynth)) {
				// Sprawd inne kierunki
				if (!wall_collision_left(labirynth)) {
					p.x -= SPEED / 2.0; // Ruch w lewo
				}
				else if (!wall_collision_right(labirynth)) {
					p.x += SPEED / 2.0; // Ruch w prawo
				}
				else if (!wall_collision_up(labirynth)) {
					p.y -= SPEED / 2.0; // Ruch w gore
				}
			}
		}

		// Sprawdzanie kolizji z granicami ekranu
		if (get_position().x <= 1) p.x += SPEED / 2.0;
		if (get_position().x >= WIDTH - 41) p.x -= SPEED / 2.0;
		if (get_position().y <= 1) p.y += SPEED / 2.0;
		if (get_position().y >= HEIGHT - 41) p.y -= SPEED / 2.0;
	}

	// Sprawdzanie kolizji w lewo
	bool wall_collision_left(const labirynth& labirynth) {
		FloatRect ghostBounds = get_bounding_box();
		ghostBounds.left -= SPEED / 2.0;
		for (const auto& wall : labirynth.get_walls()) {
			if (wall.check_collision(ghostBounds)) return true;
		}
		return false;
	}

	// Sprawdzanie kolizji w prawo
	bool wall_collision_right(const labirynth& labirynth) {
		FloatRect ghostBounds = get_bounding_box();
		ghostBounds.left += SPEED / 2.0;
		for (const auto& wall : labirynth.get_walls()) {
			if (wall.check_collision(ghostBounds)) return true;
		}
		return false;
	}

	// Sprawdzanie kolizji w gore
	bool wall_collision_up(const labirynth& labirynth) {
		FloatRect ghostBounds = get_bounding_box();
		ghostBounds.top -= SPEED / 2.0;
		for (const auto& wall : labirynth.get_walls()) {
			if (wall.check_collision(ghostBounds)) return true;
		}
		return false;
	}

	// Sprawdzanie kolizji w dol
	bool wall_collision_down(const labirynth& labirynth) {
		FloatRect ghostBounds = get_bounding_box();
		ghostBounds.top += SPEED / 2.0;
		for (const auto& wall : labirynth.get_walls()) {
			if (wall.check_collision(ghostBounds)) return true;
		}
		return false;
	}

	// Rysowanie duszka
	void draw(RenderWindow& window) const
	{
		CircleShape shape(15.f);
		shape.setTexture(&texture2);
		shape.setPosition(p.x, p.y);
		window.draw(shape);
	}

	// Uzyskiwanie koloru duszka

	// Uzyskiwanie bounding box dla duszka
	FloatRect get_bounding_box() const {
		CircleShape shape(15.f);
		shape.setPosition(p.x, p.y);
		return shape.getGlobalBounds();
	}
};
