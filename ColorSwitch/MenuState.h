#pragma once
#include "Interfaces.h"

template<class T>
class MenuState : public IState<T>
{

public:

	virtual int handleInput(sf::Event & event) override 
	{
		if (event.KeyPressed && event.key.code == sf::Keyboard::Return) m_postProcess(GameStart);
		return -1; 
	};
	inline virtual int processLogic(sf::Time deltaTime) override { return LoopCodes::Null; };
};