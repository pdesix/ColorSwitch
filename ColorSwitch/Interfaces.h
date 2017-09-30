#pragma once
#include <memory>
#include <functional>
#include <SFML\Graphics.hpp>
#include <vector>

enum LoopCodes
{
	Null,
	GameStart,
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
	typedef std::function<void(T &, LoopCodes)> GameCallback;
	typedef T Game;

	T & m_base;
	GameCallback m_postProcess;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;

public:
	IState(Game & baseGame, GameCallback processFunction) : m_drawables{ }, m_base{ baseGame }, m_postProcess{ processFunction } {}

	virtual void manageGraphic(sf::RenderWindow & window) 
	{  
		for (std::shared_ptr<sf::Drawable> & drawable : m_drawables)
			window.draw(*drawable);
	}

	virtual void handleInput(sf::Event & event) = 0;
	virtual void processLogic(sf::Time deltaTime) = 0;
};