#pragma once
#include "Interfaces.hpp"
#include "Player.hpp"
#include "Map.hpp"

template<class Game>
class GameState : public BaseState<Game>
{
private:
	std::shared_ptr<Player> m_player;
	Map<GameState> m_gameMap;

public:
	GameState(Game & baseGame, GameCallback processFunction) 
		: BaseState<Game>(baseGame, processFunction), m_player{ new Player() }, m_gameMap{m_drawables, m_player,*this,&Player::onColorChange,&GameState::onDeath, &GameState::onPoint}
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