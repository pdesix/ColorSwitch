#pragma once
#include "Interfaces.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Exceptions.hpp"

template<class Game>
class GameScene : public BaseScene<Game>
{
private:
	std::shared_ptr<Player> m_player;
	Map<GameScene> m_gameMap;
	sf::Font m_colorFont;
	std::shared_ptr<sf::Text> m_colorText;
	bool m_textActive;
	std::chrono::steady_clock::time_point m_textSet;

	void hideText()
	{
		m_colorText->setPosition(-500.f, -500.f);
		m_textActive = false;
	}

public:
	GameScene(Game & baseGame, GameCallback processFunction) 
		: BaseScene<Game>(baseGame, processFunction), 
		m_player{ new Player() }, 
		m_gameMap{ m_drawables, m_player, *this },
		m_colorText{ new sf::Text{"Red", m_colorFont, 30u} },
		m_textActive{ false }
	{ 
		m_drawables.push_back(m_player);
		if (!m_colorFont.loadFromFile("assets/reitam.otf")) throw FileNotFoundException("assets/reitam.otf");
		m_colorText->setOutlineColor(sf::Color::Black);
		m_colorText->setOutlineThickness(5.f);
		m_colorText->setPosition(10000.f, 10000.f);

		m_drawables.push_back(m_colorText);
	}

	virtual void manageGraphic(sf::RenderWindow & window) override
	{
		window.clear(sf::Color(91u, 91u, 91u));
		BaseScene<Game>::manageGraphic(window);
	}

	virtual void handleInput(sf::Event & event) override
	{
		if (event.type == sf::Event::Closed)
			runCallback(LoopCodes::GameClose);
		if (event.MouseButtonPressed && event.key.code == sf::Mouse::Left)
			m_player->move();
		else if (event.KeyPressed && event.key.code == sf::Keyboard::Escape)
			runCallback(LoopCodes::GameToMenu);
	}

	void onDeath()
	{
		runCallback(LoopCodes::GameToMenu);
	}

	void onPoint()
	{
		std::string colorString;
		if (m_player->getColor() == 0) colorString = "Pink!";
		else if (m_player->getColor() == 1) colorString = "Blue!";
		else if (m_player->getColor() == 2) colorString = "Green!";
		else colorString = "Yellow!";
		m_colorText->setString(colorString);
		m_colorText->setFillColor(m_player->getFillColor());
		m_colorText->setOrigin(m_colorText->getGlobalBounds().width / 2.f, m_colorText->getGlobalBounds().height / 2.f);
		m_colorText->setPosition(180.f, 400.f);
		m_textSet = std::chrono::steady_clock::now();
		m_textActive = true;
	}

	inline virtual void processLogic(sf::Time deltaTime) override 
	{
		if (m_textActive)
			if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_textSet).count() > 1000)
				hideText();
		if (m_player->applyGravity(deltaTime))
			m_gameMap.move(deltaTime);
		m_gameMap.processLogic(deltaTime);
	}
};