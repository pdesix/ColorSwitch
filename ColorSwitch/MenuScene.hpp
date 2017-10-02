#pragma once
#include "Interfaces.hpp"
#include <array>

template<class Game>
class MenuScene : public BaseScene<Game>
{
	std::unique_ptr<sf::Font> m_font;
	std::shared_ptr<sf::Text> play;
	std::shared_ptr<sf::Text> exit;
	std::shared_ptr<sf::Text> authors;
	sf::Texture menu_texture;
	std::shared_ptr<sf::Sprite> menu_bg;

	bool up;
public:
	MenuScene(Game & baseGame, GameCallback processFunction)
		: BaseScene(baseGame, processFunction), m_font{ new sf::Font() },
		play{ new sf::Text("Play", *m_font, 100u) },
		exit{ new sf::Text("Exit", *m_font, 60u) },
		authors{ new sf::Text("Made by Patryk Desant and Mateusz Wolski", *m_font, 30u) },
		menu_texture{ sf::Texture() },
		menu_bg{ new sf::Sprite() }
	{
		if (!m_font->loadFromFile("assets/arial.ttf")) throw FileNotFoundException("assets/arial.ttf");
		if (!menu_texture.loadFromFile("assets/menu_bg.png")) throw FileNotFoundException("assets/menu_bg.png");

		menu_bg->setTexture(menu_texture);

		play->setFillColor(sf::Color::White);
		exit->setFillColor(sf::Color::White);
		authors->setFillColor(sf::Color::White);

		play->setPosition(800 / 2 - 60, 100);
		exit->setPosition(800 / 2 - 60, 300);
		authors->setPosition(50, 550);


		m_drawables.push_back(menu_bg);
		m_drawables.push_back(play);
		m_drawables.push_back(exit);
		m_drawables.push_back(authors);

		up = true;
	}

	virtual void switchOption(bool up) {
		if (up) {
			play->setCharacterSize(100u);
			exit->setCharacterSize(60u);
			up = false;
		}
		else {
			play->setCharacterSize(60u);
			exit->setCharacterSize(100u);
			up = true;
		}
	}

	virtual void handleInput(sf::Event & event) override
	{
		if (event.type == sf::Event::Closed)
			runCallback(LoopCodes::GameClose);
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Escape)
			runCallback(LoopCodes::GameToMenu);

		//menu
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Down) {
			up = false;
			switchOption(up);
		}
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Up) {
			up = true;
			switchOption(up);
		}
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Return) {
			if (up) {
				runCallback(LoopCodes::GameStart);
			}
			else {
				runCallback(LoopCodes::GameClose);
			}
		}
	}

	inline virtual void processLogic(sf::Time deltaTime) override
	{
	}
};