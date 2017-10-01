#include "Game.hpp"

Game::Game() : m_window{ sf::VideoMode{800, 600 }, "ColorSwitch" }, m_currentScene{ new MenuScene<Game>(*this,&Game::loopProcessing) }
{
	m_window.setFramerateLimit(30);
}

void Game::run()
{
	sf::Event event;
	sf::Clock clock;
	clock.restart();
	m_window.setFramerateLimit(30u);
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
			m_currentScene->handleInput(event);

		m_window.clear(sf::Color::White);
		m_currentScene->manageGraphic(m_window);
		m_window.display();

		m_currentScene->processLogic(clock.getElapsedTime());
		clock.restart();
	}
}

void Game::loopProcessing(LoopCodes signal)
{
	switch (signal) {
	case LoopCodes::GameStart:
		m_currentScene = std::make_unique<GameScene<Game>>(*this, &Game::loopProcessing);
		break;
	case LoopCodes::GameClose:
		m_window.close();
		break;
	case LoopCodes::GameToMenu:
		//m_currentScene = std::make_unique
		break;
	}
}