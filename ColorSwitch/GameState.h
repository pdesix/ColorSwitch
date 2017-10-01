#pragma once
#include "Interfaces.h"
#include "Player.h"
#include "Map.h"

template<class T>
class GameState : public IState<T>
{
private:
	std::shared_ptr<Player> m_player;
	Map<GameState> m_gameMap;

public:
	GameState(Game & baseGame, GameCallback processFunction) : IState(baseGame, processFunction), m_player{std::make_shared<Player>(Player())}, m_gameMap{m_player,*this,&Player::onColorChange,&GameState::onDeath, &GameState::onPoint}
	{ 
		m_drawables.push_back(m_player);
		std::vector<std::shared_ptr<sf::Drawable>> mapDrawables{ m_gameMap.getDrawables() };
		for (std::shared_ptr<sf::Drawable> drawable : mapDrawables)
			m_drawables.push_back(drawable);
	}

	void onDeath()
	{
		runCallback(GameStart);
	}

	void onPoint()
	{
	}

	virtual void handleInput(sf::Event & event) override { return; };
	inline virtual void processLogic(sf::Time deltaTime) override { m_gameMap.processLogic(deltaTime); };
};