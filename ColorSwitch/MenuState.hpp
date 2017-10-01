#pragma once
#include "Interfaces.hpp"

template<class Game>
class MenuState : public StateManager<Game>
{
public:
	MenuState(Game & baseGame, GameCallback processFunction) : StateManager(baseGame,processFunction) 
	{
	}

	virtual void handleInput(sf::Event & event) override
	{
		if (event.KeyPressed && event.key.code == sf::Keyboard::Return) 
			runCallback(LoopCodes::GameStart);
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			runCallback(LoopCodes::GameClose);
	};

	inline virtual void processLogic(sf::Time deltaTime) override 
	{ 
	};
};