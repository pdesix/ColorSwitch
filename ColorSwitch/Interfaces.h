#pragma once
#include <memory>
#include <SFML\Graphics.hpp>

enum Codes
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
	virtual int manageGraphic(std::shared_ptr<sf::RenderWindow> window) = 0;
};

class ILogicProcessor
{
public:
	virtual int processLogic(sf::Time deltaTime) = 0;
};

class IState: public IInputController, public IGraphicManager, public ILogicProcessor
{
public:
	virtual int manageGraphic(std::shared_ptr<sf::RenderWindow> window) = 0;
	virtual int handleInput(sf::Event & event) = 0;
	virtual int processLogic(sf::Time deltaTime) = 0;
};