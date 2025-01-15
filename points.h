#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
using namespace sf;
using namespace std;

class punkt {
private:
	sf::CircleShape shape;
public:
	punkt(const float x, const float y, const float radius = 10.f) {
		shape.setPosition(x, y);
		shape.setRadius(radius);
		shape.setFillColor(sf::Color::White); // Mozesz ustawiæ dowolny kolor
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
	vector<punkt> points; // Przechowywanie punktow
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
			remove_if(points.begin(), points.end(),
				[&](const punkt& point) {return pacman_bounds.intersects(point.get_bounding_box()); }), points.end());
	}
	// Zwraca wektor punktow
	const vector<punkt>& get_punkty() const {
		return points;
	}
	void clear() {
		points.clear();
	}
};
