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

	void onDeath()
	{
		runCallback(LoopCodes::GameStart);
	}

	void onPoint()
	{
	}

	inline virtual void processLogic(sf::Time deltaTime) override 
	{ 
		m_gameMap.processLogic(deltaTime); 
	}
};