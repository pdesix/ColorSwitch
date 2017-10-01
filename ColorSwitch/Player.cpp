#include "Player.hpp"

Player::Player() :m_distribution(0,3), m_colors{ sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Green } 
{
	setFillColor(sf::Color::Green);
}

Player::~Player()
{
}

void Player::onColorChange()
{
	m_randNum = m_distribution(m_generator);
	setFillColor(m_colors[m_randNum]);
}
