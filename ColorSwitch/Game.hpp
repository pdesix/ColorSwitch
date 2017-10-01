#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Interfaces.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"

int main();

class Game
{
	sf::RenderWindow m_window;
	std::unique_ptr<BaseScene<Game>> m_currentScene;
	void loopProcessing(LoopCodes signal);

public:
	Game();
	void run();
};