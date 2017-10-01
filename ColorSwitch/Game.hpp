#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Interfaces.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"

int main();

class Game
{
	sf::RenderWindow m_window;
	std::unique_ptr<StateManager<Game>> m_currentState;
	void loopProcessing(LoopCodes signal);

public:
	Game();
	~Game();
	void run();
};