#include "Game.h"

void Game::ProcessCode(int returnCode)
{
}

Game::Game() : m_window(new sf::RenderWindow(sf::VideoMode(800, 600), "Tanks")), currentState{ std::make_shared<IState>() }
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
			processCode(m_inputController->handleInput(event));

		m_window->clear(sf::Color::White);
		m_currentState->manageGraphic(m_window);
		m_window->display();

		processCode(m_currentState->processLogic(clock.getElapsedTime()));
		clock.restart();
	}
}