#pragma once
#include "Interfaces.hpp"

template<class Game>
class MenuScene : public BaseScene<Game>
{
public:
	MenuScene(Game & baseGame, GameCallback processFunction) : BaseScene(baseGame, processFunction)
	{
	}

	virtual void handleInput(sf::Event & event) override
	{
		if (event.KeyPressed && event.key.code == sf::Keyboard::Return) 
			runCallback(LoopCodes::GameStart);
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			runCallback(LoopCodes::GameClose);
	}

	inline virtual void processLogic(sf::Time deltaTime) override 
	{ 
	}
};