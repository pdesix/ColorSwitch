#include "Player.h"

Player::Player() {
	setFillColor(sf::Color::Green);

	colors[0] = sf::Color::Blue;
	colors[1] = sf::Color::Yellow;
	colors[2] = sf::Color::Red;
	colors[3] = sf::Color::Magenta;
}

Player::~Player()
{
}

void Player::generateRandomColor() { //losuje numer od 0 do 3
	rand_num = rand() % 3;
}

void Player::changeColor() { //ustawia kolor w zaleznosci od wyloswaniej liczby^
	setFillColor(colors[rand_num]);
}
