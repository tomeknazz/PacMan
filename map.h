#pragma once
#include "points.h"

class wall {
public:
	sf::RectangleShape shape;

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
	labirynth() = default;

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
	void clear_walls() {
		walls.clear();
	}
};
