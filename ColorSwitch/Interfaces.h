#pragma once
#include <memory>
#include <functional>
#include <SFML\Graphics.hpp>

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
	virtual int handleInput(sf::Event & event) = 0;
};

class IGraphicManager
{
public:
	virtual int manageGraphic(sf::RenderWindow & window) = 0;
};

class ILogicProcessor
{
public:
	virtual int processLogic(sf::Time deltaTime) = 0;
};

template<class T>
class IState: public IInputController, public IGraphicManager, public ILogicProcessor
{
protected:
	std::function<void(const T &, LoopCodes)> m_postProcess;
public:
	virtual int manageGraphic(sf::RenderWindow & window) = 0;
	virtual int handleInput(sf::Event & event) = 0;
	virtual int processLogic(sf::Time deltaTime) = 0;
};