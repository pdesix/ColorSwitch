#pragma once
#include "Interfaces.h"
#include "Player.h"

class Obstacle : public sf::Sprite
{
	class ObstacleInternal : public sf::Sprite { };
	ObstacleInternal m_intern;
public:
	void move()
	{
		sf::Sprite::move(0.0, 10.0);
		m_intern.move(0.0, 10.0);
	}
	void checkCollision()
	{
		float rotation{ sf::Sprite::getRotation() };
	}
};

template<class T>
class Map : public ILogicProcessor
{
	T & m_base;
	std::function<void(T &)> m_playerDeathCallback;
	std::function<void(T &)> m_pointGainedCallback;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
	std::shared_ptr<Player> m_player;

public:
	Map(std::shared_ptr<Player> playerPointer, T& gameController, std::function<void(T &)> deathCallback, std::function<void(T &)> pointCallback) : m_base{ gameController } m_playerDeathCallback { deathCallback }, m_pointGainedCallback{ pointCallback }, m_player{ playerPointer } {}
	~Map() { }
	std::vector<std::shared_ptr<sf::Drawable>> getDrawables() { return m_drawables; }

	virtual void processLogic(sf::Time deltaTime) override
	{

	}
};

