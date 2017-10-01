#include "Player.hpp"

Player::Player() : m_distribution(0,3), m_colors{ sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Green }, m_movement{0.f,0.f}
{
	onColorChange();
	setRadius(15.f);
	setOrigin(getGlobalBounds().width/2.f, getGlobalBounds().width/2.f);

	setPosition(400.f, 450.f);
}

void Player::onColorChange()
{
	m_randNum = m_distribution(m_generator);
	setFillColor(m_colors[m_randNum]);
}

bool Player::applyGravity(sf::Time deltaTime)
{
	m_movement.y += 6.f * deltaTime.asSeconds();
	sf::CircleShape::move(m_movement);

	if (getPosition().y < 350.f)
		return true;
	else return false;
}

void Player::move()
{
	m_movement.y -= 3.f;
}