#pragma once
#include "Interfaces.hpp"
#include <array>

template<class Game>
class MenuScene : public BaseScene<Game>
{
	std::unique_ptr<sf::Font> m_font;
public:
	MenuScene(Game & baseGame, GameCallback processFunction) : BaseScene(baseGame, processFunction), m_font{new sf::Font()}
	{
		std::shared_ptr<sf::Text> play{ new sf::Text("Play", *m_font, 60u) };
		std::shared_ptr<sf::Text> exit{ new sf::Text("Exit", *m_font, 60u) };

		if (!m_font->loadFromFile("assets/arial.ttf")) {
			std::cerr << "cannot load assets/arial.ttf";
		}

		play->setFillColor(sf::Color::Black);
		exit->setFillColor(sf::Color::Black);

		play->setPosition(800 / 2, 20);
		exit->setPosition(800 / 2, 200);
		
		m_drawables.push_back(play);
		m_drawables.push_back(exit);
	}

	virtual void handleInput(sf::Event & event) override
	{
		if (event.KeyPressed && event.key.code == sf::Keyboard::Return) 
			runCallback(LoopCodes::GameStart);
		else if (event.type == sf::Event::Closed)
			runCallback(LoopCodes::GameClose);
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Escape)
			runCallback(LoopCodes::GameToMenu);
	}

	inline virtual void processLogic(sf::Time deltaTime) override 
	{ 
	}
};