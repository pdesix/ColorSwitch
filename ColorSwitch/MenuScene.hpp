#pragma once
#include "Interfaces.hpp"
#include <array>

template<class Game>
class MenuScene : public BaseScene<Game>
{
	std::unique_ptr<sf::Font> m_font;
	std::shared_ptr<sf::Text> play;
	std::shared_ptr<sf::Text> shop;
	std::shared_ptr<sf::Text> exit;
	std::shared_ptr<sf::Text> authors;
	sf::Texture menu_texture;
	std::shared_ptr<sf::Sprite> menu_bg;

	int selected;
public:
	MenuScene(Game & baseGame, GameCallback processFunction)
		: BaseScene(baseGame, processFunction), m_font{ new sf::Font() },
		play{ new sf::Text("Play", *m_font, 100u) },
		shop{ new sf::Text("Shop", *m_font, 60u) },
		exit{ new sf::Text("Exit", *m_font, 60u) },
		authors{ new sf::Text("Made by Patryk Desant and Mateusz Wolski", *m_font, 30u) },
		menu_texture{ sf::Texture() },
		menu_bg{ new sf::Sprite() }
	{
		if (!m_font->loadFromFile("assets/arial.ttf")) throw FieNoutFoundException("assets/arial.ttf");
		if (!menu_texture.loadFromFile("assets/menu_bg.png")) throw FieNoutFoundException("assets/menu_bg.png");

		menu_bg->setTexture(menu_texture);

		play->setFillColor(sf::Color::White);
		shop->setFillColor(sf::Color::White);
		exit->setFillColor(sf::Color::White);
		authors->setFillColor(sf::Color::White);

		play->setPosition(800 / 2 - 60, 100);
		shop->setPosition(800 / 2 - 60, 250);
		exit->setPosition(800 / 2 - 60, 350);
		authors->setPosition(50, 550);


		m_drawables.push_back(menu_bg);
		m_drawables.push_back(play);
		m_drawables.push_back(shop);
		m_drawables.push_back(exit);
		m_drawables.push_back(authors);

		selected = 1;
	}

	virtual void switchOption(int selected) {
		if (selected == 1) {
			play->setCharacterSize(100u);
			shop->setCharacterSize(60u);
			exit->setCharacterSize(60u);
		}
		else if (selected == 2) {
			play->setCharacterSize(60u);
			shop->setCharacterSize(100u);
			exit->setCharacterSize(60u);
		}
		else if (selected == 3) {
			play->setCharacterSize(60u);
			shop->setCharacterSize(60u);
			exit->setCharacterSize(100u);
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
			switchOption(++selected);
		}
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Up) {
			switchOption(--selected);
		}
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Return) {
			if (selected == 1) {
				runCallback(LoopCodes::GameStart);
			}
			else if(selected == 3){
				runCallback(LoopCodes::GameClose);
			}
		}
	}

	inline virtual void processLogic(sf::Time deltaTime) override
	{
	}
};