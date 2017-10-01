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

template<class T>
class IState: public IInputController, public IGraphicManager, public ILogicProcessor
{
protected:
	typedef T Game;
	typedef std::function<void(Game &, LoopCodes)> GameCallback;

private:
	Game & m_base;
	GameCallback m_postProcess;

protected:
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;

	void runCallback(LoopCodes code)
	{
		m_postProcess(m_base, code);
	}

public:
	IState(Game & baseGame, GameCallback processFunction) : m_base{ baseGame }, m_postProcess{ processFunction } {}

	virtual void handleInput(sf::Event & event) = 0;
	virtual void processLogic(sf::Time deltaTime) = 0;

	virtual void manageGraphic(sf::RenderWindow & window)
	{
		for (std::shared_ptr<sf::Drawable> & drawable : m_drawables)
			window.draw(*drawable);
	}
};