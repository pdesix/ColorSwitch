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
	std::function<void(T &, LoopCodes)> m_postProcess;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
public:
	virtual int manageGraphic(sf::RenderWindow & window) 
	{ 
		window.clear(sf::Color::White);  
		for (std::shared_ptr<sf::Drawable> & drawable : m_drawables)
			drawable->draw(window);
		window.display();
	}

	virtual int handleInput(sf::Event & event) = 0;
	virtual int processLogic(sf::Time deltaTime) = 0;
	inline virtual void updatePostProcess(std::function<void(T &, LoopCodes)> postProcessFunction) { m_postProcess = postProcessFunction; }
};