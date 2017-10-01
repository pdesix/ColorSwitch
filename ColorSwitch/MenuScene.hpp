#pragma once
#include "Interfaces.hpp"
#include <array>

template<class Game>
class MenuScene : public BaseScene<Game>
{
public:
	MenuScene(Game & baseGame, GameCallback processFunction) : BaseScene(baseGame, processFunction)
	{
		//std::shared_ptr<sf::Text>(play);
		//std::shared_ptr<sf::Text>(exit);
		sf::Text play;
		sf::Text exit;
		sf::Font font;

		if (!font.loadFromFile("assets/arial.ttf")) {
			std::cerr << "cannot load assets/arial.ttf";
		}

		std::array<std::string, 2> words = { "Play", "Exit" };

		play.setFont(font);
		exit.setFont(font);

		play.setString(words[0]);
		exit.setString(words[1]);

		play.setCharacterSize(60);
		exit.setCharacterSize(60);

		play.setFillColor(sf::Color::Black);
		exit.setFillColor(sf::Color::Black);

		play.setPosition(800 / 2, 20);
		exit.setPosition(800 / 2, 200);
		
		m_drawables.push_back(std::make_shared<sf::Text>(play));
		m_drawables.push_back(std::make_shared<sf::Text>(exit));
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