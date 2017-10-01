#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Interfaces.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"

int main();

class Game
{
	std::unique_ptr<sf::RenderWindow> m_window;
	std::unique_ptr<IState<Game>> m_currentState;
	void loopProcessing(LoopCodes signal);

public:
	Game();
	~Game();
	void run();
};