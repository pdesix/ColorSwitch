#pragma once
#include "Interfaces.h"

template<class T>
class GameState : public IState, public sf::CircleShape<T>
{
private:
	sf::CircleShape player;
public:
	GameState() {
		
	}
	inline virtual int manageGraphic(std::shared_ptr<sf::RenderWindow> window) override
	{
		window->clear(sf::Color::White);
		window->draw(player);
		window->display();
		return -1;
	}
	virtual int handleInput(sf::Event & event) override { return -1; };
	inline virtual int processLogic(sf::Time deltaTime) override { return LoopCodes::Null; };
};

