#pragma once
#include "Interfaces.h"

template<class T>
class MenuState : public IState<T>
{
public:
	MenuState(T & baseGame, std::function<void(T &, LoopCodes)> processFunction) : IState(baseGame,processFunction) { }

	virtual void handleInput(sf::Event & event) override
	{
		sf::CircleShape x;
		m_drawables.push_back(std::make_shared<sf::CircleShape>(x));
		if (event.KeyPressed && event.key.code == sf::Keyboard::Return) 
			m_postProcess(m_base,GameStart);
	};
	inline virtual void processLogic(sf::Time deltaTime) override { };
};