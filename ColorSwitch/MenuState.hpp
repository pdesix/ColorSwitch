#pragma once
#include "Interfaces.hpp"

template<class T>
class MenuState : public IState<T>
{
public:
	MenuState(Game & baseGame, GameCallback processFunction) : IState(baseGame,processFunction) 
	{
	}

	virtual void handleInput(sf::Event & event) override
	{
		if (event.KeyPressed && event.key.code == sf::Keyboard::Return) 
			runCallback(GameStart);
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			runCallback(GameClose);
	};

	inline virtual void processLogic(sf::Time deltaTime) override 
	{ 
	};
};