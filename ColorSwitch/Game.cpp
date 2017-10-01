#include "Game.hpp"

Game::Game() : m_window{ sf::VideoMode{800, 600 }, "ColorSwitch" }, m_currentState{ new MenuState<Game>(*this,&Game::loopProcessing) }
{
	m_window.setFramerateLimit(30);
}


Game::~Game()
{
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
			m_currentState->handleInput(event);

		m_window.clear(sf::Color::White);
		m_currentState->manageGraphic(*m_window);
		m_window.display();

		m_currentState->processLogic(clock.getElapsedTime());
		clock.restart();
	}
}

void Game::loopProcessing(LoopCodes signal)
{
	switch (signal) {
	case LoopCodes::GameStart:
		m_currentState = std::make_unique<GameState<Game>>(GameState<Game>(*this, &Game::loopProcessing));
		break;
	case LoopCodes::GameClose:
		m_window.close();
		break;
	}
}