#pragma once
#include "Interfaces.h"
#include "Player.h"

template<class T>
class Obstacle : public sf::CircleShape
{
	typedef T GameState;
	typedef std::function<void(GameState &)> GameStateFunction;

	GameState & m_base;
	std::shared_ptr<sf::CircleShape> m_intern;
	std::shared_ptr<Player> m_player;
	GameStateFunction m_playerDeath;

	sf::Texture* m_circleTexture;

public:
	Obstacle(int i, std::shared_ptr<Player> gamePlayer, GameState & baseObject, GameStateFunction playerDeathCallback) : m_base{ baseObject }, m_player { gamePlayer }, m_playerDeath{ playerDeathCallback }, m_intern{std::make_shared<sf::CircleShape>()}, m_circleTexture{new sf::Texture()}
	{
		if (!m_circleTexture->loadFromFile("assets/data001.png")) std::cerr << "cannot load assets/data001.png";
		setTexture(m_circleTexture,true);
		
		m_intern->setFillColor(sf::Color::Red);
		setFillColor(sf::Color::Black);

		setRadius(25.f);
		m_intern->setRadius(20.f);

		setPosition(400.f - (getGlobalBounds().width / 2), -150.f * i);
		m_intern->setPosition(this->getPosition().x - m_intern->getGlobalBounds().height/8, this->getPosition().y + m_intern->getGlobalBounds().width/8);
	}

	std::shared_ptr<sf::CircleShape> getInternalDrawable() { return m_intern; }

	void move()
	{
		setPosition(getPosition().x, getPosition().y + 5.f);
		m_intern->setPosition(m_intern->getPosition().x, m_intern->getPosition().y + 5.f);
		
		std::cout << "Pos: " << getPosition().x << " ; " << getPosition().y << " \n";
		std::cout << "\t intern pos: " << m_intern->getPosition().x << " ; " << m_intern->getPosition().y << " \n";

		rotate(1.f);
		m_intern->rotate(1.f);

		while (getPosition().y > 950.f) setPosition(getPosition().x, getPosition().y - 650.f);
		while (m_intern->getPosition().y > 950.f) m_intern->setPosition(m_intern->getPosition().x, m_intern->getPosition().y - 650.f);
	}
	
	void checkCollision()
	{
		if (m_player->getGlobalBounds().intersects(sf::Sprite::getGlobalBounds()))
		{
			auto color{ []
			{
				float rotation{ sf::Sprite::getRotation() };
				if (static_cast<int>{rotation} % 90 < 10) return -1;
				else return static_cast<int>{rotation / 90.f};
			}(); };
			if (m_player->getColor() != color && m_player->getGlobalBounds().intersects(m_intern->getGlobalBounds()) == false) { return m_base->m_playerDeath(); }
		}

	}
};

template<class T>
class Map : public ILogicProcessor
{
	typedef T GameState;
	typedef std::function<void(GameState &)> GameStateFunction;
	typedef std::function<void(Player&)> PlayerFunction;

	GameState & m_base;
	GameStateFunction m_playerDeathCallback;
	GameStateFunction m_pointGainedCallback;
	PlayerFunction m_playerCollorChanged;

	std::shared_ptr<Player> m_player;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
	std::vector<std::shared_ptr<Obstacle<GameState>>> m_obstacles;

public:
	Map(std::shared_ptr<Player> playerPointer, GameState & gameController, PlayerFunction playerCollorChangedCallback, GameStateFunction deathCallback, GameStateFunction pointCallback)
		: m_base{ gameController }, m_playerDeathCallback { deathCallback }, m_pointGainedCallback{ pointCallback }, m_player{ playerPointer }, m_playerCollorChanged{ playerCollorChangedCallback }
	{
		for (int i = 0; i < 1; i++)
		{
			std::shared_ptr<Obstacle<GameState>> obstacle{ std::make_shared<Obstacle<GameState>>(i, playerPointer, gameController, deathCallback) };

			m_drawables.push_back(obstacle);
			m_obstacles.push_back(obstacle);

			m_drawables.push_back(obstacle->getInternalDrawable());
		}
	}

	~Map() { }
	std::vector<std::shared_ptr<sf::Drawable>> getDrawables() { return m_drawables; }

	virtual void processLogic(sf::Time deltaTime) override
	{
		for (std::shared_ptr<Obstacle<GameState>> obstacle : m_obstacles)
			obstacle->move();
	}
};

