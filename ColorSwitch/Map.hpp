#pragma once
#include "Interfaces.hpp"
#include "Player.hpp"

template<class GameScene>
class ColorSwitcher : public sf::CircleShape
{
	using PlayerFunction = std::function<void(Player&)>;
	PlayerFunction m_playerCollorChanged;

	std::shared_ptr<Player> m_player;

	bool m_active;

public:
	ColorSwitcher(sf::Vector2f position, std::shared_ptr<Player> player) 
		: m_active{ true }, m_playerCollorChanged{ &Player::onColorChange }, m_player{ player }
	{
		setRadius(10.f);
		setPosition(position.x,position.y);
	}

	void setPosition(float x, float y)
	{
		if (!m_active) return;
		sf::CircleShape::setPosition(x, y);
	}

	void switchActivity()
	{
		if (m_active)
		{
			m_playerCollorChanged(*m_player);
			setPosition(-500.f, -500.f);
		}
		m_active = !m_active;
	}

	bool isActive()
	{
		return m_active;
	}
};

template<class GameScene>
class Obstacle : public sf::CircleShape
{
	using GameSceneFunction = std::function<void(GameScene &)>;

	GameScene & m_base;
	std::shared_ptr<sf::CircleShape> m_intern;
	std::shared_ptr<Player> m_player;
	GameSceneFunction m_playerDeath;
	std::shared_ptr<ColorSwitcher<GameScene>> m_switcher;

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

		setPosition(400.f, -350.f * positionIndex);

		float pX = getGlobalBounds().left + getGlobalBounds().width / 2.f;
		float pY = getGlobalBounds().top + getGlobalBounds().height / 2.f;
		m_intern->setPosition(pX, pY);

		m_switcher = std::make_shared<ColorSwitcher<GameScene>>( ColorSwitcher<GameScene>(sf::CircleShape::getPosition(), m_player) );
	}

	std::shared_ptr<sf::CircleShape> getInternalDrawable() { return m_intern; }
	std::shared_ptr<sf::CircleShape> getColorSwitcher() { return m_switcher; }

	void rotate(sf::Time deltaTime)
	{
		sf::CircleShape::rotate(60.f * deltaTime.asSeconds());
		m_intern->rotate(60.f * deltaTime.asSeconds());
	}

	void move(sf::Time deltaTime)
	{
		while (getPosition().y > 750.f)
		{
			if (!m_switcher->isActive()) m_switcher->switchActivity();
			sf::CircleShape::move(0.f, -750.f);
			m_intern->move(0.f, -750.f);
		}

		sf::CircleShape::move(0.f, 60.f*deltaTime.asSeconds());
		m_intern->move(0.f, 60.f*deltaTime.asSeconds());
		m_switcher->move(0.f, 60.f*deltaTime.asSeconds());
	}
	
	bool checkCollision()
	{
		sf::FloatRect playerBounds{ m_player->getGlobalBounds() };
		playerBounds.height -= 7.5f;
		playerBounds.top += 7.5f;
		if (playerBounds.intersects(sf::CircleShape::getGlobalBounds()))
		{
			auto color = [&]
			{
				if (m_player->getPosition().y > getGlobalBounds().top + getGlobalBounds().width)
				{
					float rotation{ sf::CircleShape::getRotation() };
					if (static_cast<int>(rotation) % 90 < 10) return -1;
					else return static_cast<int>(rotation / 90.f);
				}
				else
				{
					float rotation{ sf::CircleShape::getRotation() };
					if (static_cast<int>(rotation) % 90 < 10) return -1;
					else return (static_cast<int>(rotation / 90.f) + 2)%4;
				}
			}();
			if (m_player->getColor() != color && playerBounds.intersects(m_intern->getGlobalBounds()) == false)
			{ 
				m_playerDeath(m_base);
				return true;
			}
		}
		return false;
	}
};

template<class GameScene>
class Map : public ILogicProcessor
{
	using GameSceneFunction = std::function<void(GameScene &)>;
	using PlayerFunction = std::function<void(Player&)>;

	GameScene & m_base;
	GameSceneFunction m_pointGainedCallback;

	std::shared_ptr<Player> m_player;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
	std::vector<std::shared_ptr<Obstacle<GameScene>>> m_obstacles;

	std::shared_ptr<sf::Texture> m_circleTexture;

public:
	Map(std::vector<std::shared_ptr<sf::Drawable>> & drawables, std::shared_ptr<Player> playerPointer, GameScene & gameController)
		: m_base{ gameController }, m_player{ playerPointer }, m_circleTexture{ new sf::Texture() },
		m_pointGainedCallback{ &GameScene::onPoint }
	{
		if (!m_circleTexture->loadFromFile("assets/data001.png")) std::cerr << "cannot load assets/data001.png";
		for (int i = 0; i < 1; i++)
		{
			std::shared_ptr<Obstacle<GameScene>> obstacle{ new Obstacle<GameScene>(i, playerPointer, gameController) };

	 		obstacle->setTexture(&(*m_circleTexture), true);
			obstacle->getColorSwitcher()->setTexture(&(*m_circleTexture), true);

			drawables.push_back(obstacle);
			drawables.push_back(obstacle->getInternalDrawable());
			drawables.push_back(obstacle->getColorSwitcher());

			m_obstacles.push_back(obstacle);
		}
	}

	void move(sf::Time deltaTime)
	{
		for (std::shared_ptr<Obstacle<GameScene>> obstacle : m_obstacles)
			obstacle->move(deltaTime);
	}

	virtual void processLogic(sf::Time deltaTime) override
	{
		for (std::shared_ptr<Obstacle<GameScene>> obstacle : m_obstacles)
		{
			obstacle->rotate(deltaTime);
			if (obstacle->checkCollision()) break;
		}
	}
};

