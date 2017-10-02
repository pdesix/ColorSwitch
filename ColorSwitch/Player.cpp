#include "Player.hpp"

Player::Player() : m_distribution(0, 3), m_generator{ std::clock() }, m_colors{ sf::Color{154,137,164}, sf::Color{ 54,137,193 }, sf::Color{0,122,88}, sf::Color{ 165,137,11 }}, m_movement{ 0.f,0.f }
{
	onColorChange();
	setRadius(10.f);
	setOrigin(getGlobalBounds().width/2.f, getGlobalBounds().width/2.f);

	setPosition(180.f, 240.f);
}

void Player::onColorChange()
{
	int tempRandNum{ m_randNum};
	while(tempRandNum == m_randNum)
		tempRandNum = m_distribution(m_generator);
	m_randNum = tempRandNum;
	setFillColor(m_colors[m_randNum]);
}

bool Player::applyGravity(sf::Time deltaTime)
{
	m_movement.y += 10.f * deltaTime.asSeconds();
	sf::CircleShape::move(m_movement);

	if (getPosition().y < 350.f)
		return true;
	else return false;
}

void Player::move()
{
	m_movement.y -= 5.f;
}