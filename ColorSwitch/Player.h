#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player : public sf::CircleShape {
private:
	std::vector<sf::Color> colors;
	int rand_num;
public:
	Player();
	~Player();
	int getColor() { return 0; }

	void generateRandomColor();
	void changeColor();
};

