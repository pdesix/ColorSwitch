#pragma once
#include "Interfaces.h"
#include "Player.h"

template<class T>
class Obstacle : public sf::Sprite
{
	typedef std::function<void(T &)> GameFunction;
	typedef T Game;

	Game & m_base;
	class ObstacleInternal : public sf::Sprite { };
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
	typedef std::function<void(T &)> GameFunction;
	typedef std::function<void(Player&)> PlayerFunction;
	typedef T Game;

	Game & m_base;
	std::function<void(T &)> m_playerDeathCallback;
	std::function<void(T &)> m_pointGainedCallback;
	std::function<void(Player &)> m_playerCollorChanged;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
	std::shared_ptr<Player> m_player;

public:
	Map(std::shared_ptr<Player> playerPointer, Game & gameController, PlayerFunction playerCollorChangedCallback, GameFunction deathCallback, GameFunction pointCallback) : m_base{ gameController } m_playerDeathCallback { deathCallback }, m_pointGainedCallback{ pointCallback }, m_player{ playerPointer }, m_playerCollorChanged{ playerCollorChangedCallback } {}
	~Map() { }
	std::vector<std::shared_ptr<sf::Drawable>> getDrawables() { return m_drawables; }

	virtual void processLogic(sf::Time deltaTime) override
	{

	}
};

