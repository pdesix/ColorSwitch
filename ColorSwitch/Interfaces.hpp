#pragma once
#include <memory>
#include <functional>
#include <SFML\Graphics.hpp>
#include <vector>

enum class LoopCodes
{
	Null,
	GameStart,
	GameClose,
	GameLose,
	GameWin,
	GameError,
	GameToMenu,
	GamePause,
	GameResume
};

class IInputController
{
public:
	virtual void handleInput(sf::Event & event) = 0;
};

class IGraphicManager
{
public:
	virtual void manageGraphic(sf::RenderWindow & window) = 0;
};

class ILogicProcessor
{
public:
	virtual void processLogic(sf::Time deltaTime) = 0;
};

class IState : public IInputController, IGraphicManager, ILogicProcessor
{
public:
	virtual void manageGraphic(sf::RenderWindow & window) = 0;
	virtual void handleInput(sf::Event & event) = 0;
	virtual void processLogic(sf::Time deltaTime) = 0;
};

template<class Game>
class BaseState : public IState
{
protected:
	using GameCallback = std::function<void(Game &, LoopCodes)>;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;

private:
	Game & m_base;
	GameCallback m_postProcess;

protected:
	void runCallback(LoopCodes code)
	{
		m_postProcess(m_base, code);
	}

public:
	BaseState(Game & baseGame, GameCallback processFunction) : m_base{ baseGame }, m_postProcess{ processFunction }
	{
	}

	virtual void manageGraphic(sf::RenderWindow & window) override
	{
		for (std::shared_ptr<sf::Drawable> & drawable : m_drawables)
			window.draw(*drawable);
	}

	virtual void handleInput(sf::Event & event) override
	{
	}

	virtual void processLogic(sf::Time deltaTime) override
	{
	}
};