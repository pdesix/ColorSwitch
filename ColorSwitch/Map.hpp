#pragma once
#include "Interfaces.hpp"
#include "Player.hpp"

template<class GameScene>
class Obstacle : public sf::CircleShape
{
	using GameSceneFunction = std::function<void(GameScene &)>;

	GameScene & m_base;
	std::shared_ptr<sf::CircleShape> m_intern;
	std::shared_ptr<Player> m_player;
	GameSceneFunction m_playerDeath;

public:
	Obstacle(int positionIndex, std::shared_ptr<Player> gamePlayer, GameScene & baseObject) 
		: m_base{ baseObject }, m_player { gamePlayer }, m_intern{std::make_shared<sf::CircleShape>()},
		m_playerDeath{ &GameScene::onDeath }
	{
		m_intern->setFillColor(sf::Color::White);

		setRadius(75.f);
		m_intern->setRadius(65.f);

		setOrigin(getGlobalBounds().height / 2.f, getGlobalBounds().width / 2.f);
		m_intern->setOrigin(m_intern->getGlobalBounds().height / 2.f, m_intern->getGlobalBounds().width / 2.f);

		setPosition(400.f, -150.f * positionIndex);

		float pX = getGlobalBounds().left + getGlobalBounds().width / 2.f;
		float pY = getGlobalBounds().top + getGlobalBounds().height / 2.f;
		m_intern->setPosition(pX, pY);
	}

	std::shared_ptr<sf::CircleShape> getInternalDrawable() { return m_intern; }

	void move()
	{
		setPosition(getPosition().x, getPosition().y + 5.f);
		m_intern->setPosition(m_intern->getPosition().x, m_intern->getPosition().y + 5.f);
		
		rotate(1.f);
		m_intern->rotate(1.f);

		while (getPosition().y > 750.f) setPosition(getPosition().x, getPosition().y - 750.f);
		while (m_intern->getPosition().y > 750.f) m_intern->setPosition(m_intern->getPosition().x, m_intern->getPosition().y - 750.f);
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

template<class GameScene>
class Map : public ILogicProcessor
{
	using GameSceneFunction = std::function<void(GameScene &)>;
	using PlayerFunction = std::function<void(Player&)>;

	GameScene & m_base;
	GameSceneFunction m_pointGainedCallback;
	PlayerFunction m_playerCollorChanged;

	std::shared_ptr<Player> m_player;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
	std::vector<std::shared_ptr<Obstacle<GameScene>>> m_obstacles;

	std::shared_ptr<sf::Texture> m_circleTexture;

public:
	Map(std::vector<std::shared_ptr<sf::Drawable>> & drawables, std::shared_ptr<Player> playerPointer, GameScene & gameController)
		: m_base{ gameController }, m_player{ playerPointer }, m_circleTexture{ new sf::Texture() },
		m_pointGainedCallback{ &GameScene::onPoint }, m_playerCollorChanged{ &Player::onColorChange }
	{
		if (!m_circleTexture->loadFromFile("assets/data001.png")) std::cerr << "cannot load assets/data001.png";
		for (int i = 0; i < 1; i++)
		{
			std::shared_ptr<Obstacle<GameScene>> obstacle{ new Obstacle<GameScene>(i, playerPointer, gameController) };

	 		obstacle->setTexture(&(*m_circleTexture), true);

			drawables.push_back(obstacle);
			drawables.push_back(obstacle->getInternalDrawable());

			m_obstacles.push_back(obstacle);
		}
	}

	virtual void processLogic(sf::Time deltaTime) override
	{
		for (std::shared_ptr<Obstacle<GameScene>> obstacle : m_obstacles)
			obstacle->move();
	}
};

