#pragma once
#include "Interfaces.hpp"
#include "Player.hpp"
#include "Map.hpp"

template<class Game>
class GameScene : public BaseScene<Game>
{
private:
	std::shared_ptr<Player> m_player;
	Map<GameScene> m_gameMap;

public:
	GameScene(Game & baseGame, GameCallback processFunction) 
		: BaseScene<Game>(baseGame, processFunction), m_player{ new Player() }, m_gameMap{m_drawables, m_player, *this}
	{ 
		m_drawables.push_back(m_player);
	}

	virtual void handleInput(sf::Event & event) override
	{
		if (event.type == sf::Event::Closed)
			runCallback(LoopCodes::GameClose);
		if (event.MouseButtonPressed && event.key.code == sf::Mouse::Left)
			m_player->move();
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Escape)
			runCallback(LoopCodes::GameToMenu);
	}

	void onDeath()
	{
		runCallback(LoopCodes::GameToMenu);
	}

	void onPoint()
	{
	}

	inline virtual void processLogic(sf::Time deltaTime) override 
	{
		if (m_player->applyGravity(deltaTime))
			m_gameMap.move(deltaTime);
		m_gameMap.processLogic(deltaTime);
	}
};