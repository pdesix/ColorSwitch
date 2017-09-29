#pragma once
#include "Interfaces.h"

class MenuState : public IState
{

public:

	inline virtual int manageGraphic(std::shared_ptr<sf::RenderWindow> window) override 
	{ 
		window->clear(sf::Color::White); 
		return -1;
	}
	virtual int handleInput(sf::Event & event) override { return -1 };
	inline virtual int processLogic(sf::Time deltaTime) override { return Codes::Null; };
};