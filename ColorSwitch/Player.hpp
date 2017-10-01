#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <random>

class Player : public sf::CircleShape {
private:
	std::array<sf::Color, 4> m_colors;
	int m_randNum; 
	
	std::default_random_engine m_generator;
	std::uniform_int_distribution<int> m_distribution;

public:
	Player();
	int getColor() { return m_randNum; }

	void onColorChange();
};

