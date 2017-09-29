#include "Game.h"

Game::Game() : m_window{ new sf::RenderWindow(sf::VideoMode{800, 600 }, "ColorSwitch") }, m_currentState{ std::make_shared<MenuState<Game>>() }
{
	m_window->setFramerateLimit(30);
	m_inputController = m_currentState;
}


Game::~Game()
{
}

void Game::run()
{
	sf::Event event;
	sf::Clock clock;
	clock.restart();
	while (m_window->isOpen())
	{
		while (m_window->pollEvent(event))
			m_inputController->handleInput(event);

		m_window->clear(sf::Color::White);
		m_currentState->manageGraphic(m_window);
		m_window->display();

		m_currentState->processLogic(clock.getElapsedTime());
		clock.restart();
	}
}

void Game::loopProcessing(LoopCodes signal)
{

}