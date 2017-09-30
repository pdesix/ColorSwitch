#include "Game.h"

Game::Game() : m_window{ new sf::RenderWindow(sf::VideoMode{800, 600 }, "ColorSwitch") }, m_currentState{ std::make_unique<MenuState<Game>>(MenuState<Game>(*this,&Game::loopProcessing)) }
{
	m_window->setFramerateLimit(30);
	srand(time(NULL));
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
			m_currentState->handleInput(event);

		m_window->clear(sf::Color::White);
		m_currentState->manageGraphic(*m_window);
		m_window->display();

		m_currentState->processLogic(clock.getElapsedTime());
		clock.restart();
	}
}

void Game::loopProcessing(LoopCodes signal)
{
	if (signal == GameStart)
	{
		//m_currentState = std::make_shared()
	}
}