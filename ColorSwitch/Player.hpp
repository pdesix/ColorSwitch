#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <chrono>

class Player : public sf::CircleShape
{
private:
	std::array<sf::Color, 4> m_colors;
	int m_randNum; 
	
	std::default_random_engine m_generator;
	std::uniform_int_distribution<unsigned int> m_distribution;

	sf::Vector2f m_movement;

public:
	Player();
	int getColor() { return m_randNum; }

	void onColorChange();

	void move();
	bool applyGravity(sf::Time deltaTime);
};

