#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::CircleShape {
public:
	Player();
	~Player();
	int getColor() { return 0; }
};

