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
	T & m_base;
	std::function<void(T &, LoopCodes)> m_postProcess;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
public:
	IState(T & baseGame, std::function<void(T &, LoopCodes)> processFunction) : m_drawables{ 0 }, m_base{ baseGame }, m_postProcess{ processFunction } {}

	virtual void manageGraphic(sf::RenderWindow & window) 
	{ 
		window.clear(sf::Color::White);  
		for (std::shared_ptr<sf::Drawable> & drawable : m_drawables)
			window.draw(*drawable);
		window.display();
	}

	virtual void handleInput(sf::Event & event) = 0;
	virtual void processLogic(sf::Time deltaTime) = 0;
};