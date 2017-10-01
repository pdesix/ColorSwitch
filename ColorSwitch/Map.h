#pragma once
#include "Interfaces.h"
#include "Player.h"

template<class T>
class Obstacle : public sf::CircleShape
{
	typedef std::function<void(T &)> GameStateFunction;
	typedef T GameState;

	GameState & m_base;
	sf::CircleShape m_intern;
	std::shared_ptr<Player> m_player;
	std::function<void(T &)> m_playerDeath;

public:
	Obstacle(std::shared_ptr<Player> gamePlayer, GameState & baseObject, GameStateFunction playerDeathCallback) : m_base{ baseObject }, m_player { gamePlayer }, m_playerDeath{ playerDeathCallback }
	{
		m_intern.setFillColor(sf::Color::Red);
		setFillColor(sf::Color::Black);

		setRadius(25.f);
		m_intern.setRadius(20.f);

	//	setPosition(400.f - (getGlobalBounds().width / 2), -150.f * i); TODO
	//	m_intern(400.f - (m_intern.getGlobalBounds().width / 2), -150.f * i + );
	}

	sf::CircleShape& getInternalDrawable() { return m_intern; }

	void move()
	{
		setPosition(sf::Vector2f{ getPosition().x, getPosition().y + 5.f });
		m_intern.setPosition(sf::Vector2f{ m_intern.getPosition().x, m_intern.getPosition().y + 5.f });
		sf::CircleShape::rotate(1.f);

		while (getPosition().y > 650.f) setPosition(sf::Vector2f{ getPosition().x, getPosition().y - 650.f });
		while (m_intern.getPosition().y > 650) m_intern.setPosition(sf::Vector2f{ m_intern.getPosition().x, m_intern.getPosition().y - 650.f });

		// std::cout << "Pos: " << getPosition().x << " ; " << getPosition().y << " \n";
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
			if (m_player->getColor() != color && m_player->getGlobalBounds().intersects(m_intern.getGlobalBounds()) == false) { return m_base->m_playerDeath(); }
		}

	}
};

template<class T>
class Map : public ILogicProcessor
{
	typedef std::function<void(T &)> GameStateFunction;
	typedef std::function<void(Player&)> PlayerFunction;
	typedef T GameState;

	GameState & m_base;
	GameStateFunction m_playerDeathCallback;
	GameStateFunction m_pointGainedCallback;
	PlayerFunction m_playerCollorChanged;

	std::shared_ptr<Player> m_player;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
	std::vector<std::shared_ptr<Obstacle<GameState>>> m_obstacles;

	sf::Texture circleTexture;

public:
	Map(std::shared_ptr<Player> playerPointer, GameState & gameController, PlayerFunction playerCollorChangedCallback, GameStateFunction deathCallback, GameStateFunction pointCallback)
		: m_base{ gameController }, m_playerDeathCallback { deathCallback }, m_pointGainedCallback{ pointCallback }, m_player{ playerPointer }, m_playerCollorChanged{ playerCollorChangedCallback } 
	{
		if (!circleTexture.loadFromFile("assets/data001.png")) std::cerr << "cannot load assets/data001.png";
		for (int i = 0; i < 3; i++)
		{
			std::shared_ptr<Obstacle<GameState>> obstacle{ std::make_shared<Obstacle<GameState>>(playerPointer, gameController, deathCallback) };

			m_drawables.push_back(obstacle);
			m_obstacles.push_back(obstacle);

			m_drawables.push_back(std::make_shared<sf::CircleShape>(obstacle->getInternalDrawable()));
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

