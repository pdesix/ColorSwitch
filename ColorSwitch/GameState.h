#pragma once
#include "Interfaces.h"
#include "Player.h"

template<class T>
class GameState : public IState<T>
{
private:
	std::shared_ptr<Player> m_player;

public:
	GameState(Game & baseGame, GameCallback processFunction) : IState(baseGame, processFunction), m_player{std::make_shared{new Player()}} { }

	virtual void handleInput(sf::Event & event) override { return -1; };
	inline virtual void processLogic(sf::Time deltaTime) override { };
};

