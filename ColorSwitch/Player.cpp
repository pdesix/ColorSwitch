#include "Player.h"

Player::Player() :m_distribution(0,3), m_colors{ sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Magenta } 
{
	setFillColor(sf::Color::Green);
}

Player::~Player()
{
}

void Player::changeColor() //ustawia kolor w zaleznosci od wyloswaniej liczby^
{
	m_randNum = m_distribution(m_generator);
	setFillColor(m_colors[m_randNum]);
}
