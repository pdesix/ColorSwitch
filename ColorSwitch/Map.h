#pragma once
#include "Interfaces.h"
#include "Player.h"

template<class T>
class Obstacle : public sf::CircleShape
{
	typedef std::function<void(T &)> GameFunction;
	typedef T Game;

	Game & m_base;
	class ObstacleInternal : public sf::CircleShape { };
	ObstacleInternal m_intern;
	std::shared_ptr<Player> m_player;
	std::function<void(T &)> m_playerDeath;

public:
	Obstacle(std::shared_ptr<Player> gamePlayer, Game& baseObject, GameFunction playerDeathCallback) : m_base{ baseObject }, m_player { gamePlayer }, m_playerDeath{ playerDeathCallback } { }

	void move()
	{
		sf::Sprite::move(0.0, 10.0);
		m_intern.move(0.0, 10.0);
	}
	
	void setRadius(float radius) override
	{
		sf::CircleShape::setRadius(radius);
		m_intern->setRadius(radius - 5.f);
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

public:
	Map(std::shared_ptr<Player> playerPointer, GameState & gameController, PlayerFunction playerCollorChangedCallback, GameStateFunction deathCallback, GameStateFunction pointCallback)
		: m_base{ gameController }, m_playerDeathCallback { deathCallback }, m_pointGainedCallback{ pointCallback }, m_player{ playerPointer }, m_playerCollorChanged{ playerCollorChangedCallback } 
	{
		std::shared_ptr<Obstacle<GameState>> obstacle{ std::make_shared<Obstacle<GameState>>(playerPointer, gameController, deathCallback) };
		obstacle->setRadius(25.f);
	}

	~Map() { }
	std::vector<std::shared_ptr<sf::Drawable>> getDrawables() { return m_drawables; }

	virtual void processLogic(sf::Time deltaTime) override
	{

	}
};

