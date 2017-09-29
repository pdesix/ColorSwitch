#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML\Graphics.hpp>
#include "Interfaces.h"
#include "MenuState.h"

int main();

class Game
{
	std::shared_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<IState<Game>> m_currentState;
	std::shared_ptr<IInputController> m_inputController;
	void run(); 
	void loopProcessing(LoopCodes signal);

public:
	Game();
	~Game();
};