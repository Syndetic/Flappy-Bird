#include <sstream> 
#include <iostream>

#include "MainMenuState.h"
#include "DEFINITIONS.h"
#include "InputManager.h"
#include "GameState.h"

namespace fb
{
	MainMenuState::MainMenuState(gameDataRef data) : data(data) { }

	void MainMenuState::init()
	{
		data->assets.loadTexture("Main Menu State", MAIN_MENU_BACKGROUND_FILEPATH);
	    data->assets.loadTexture("Game State", GAME_TITLE_FILEPATH);
		data->assets.loadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		backgroundSprite.setTexture(this->data->assets.getTexture("Main Menu State"));
		title.setTexture(this->data->assets.getTexture("Game State"));
		playButton.setTexture(this->data->assets.getTexture("Play Button"));

		title.setPosition(
			SCREEN_WIDTH / 2 - title.getGlobalBounds().width / 2,
			title.getGlobalBounds().height / 2
			);

		playButton.setPosition(
			SCREEN_WIDTH / 2 - playButton.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - playButton.getGlobalBounds().height / 2
		);
	}

	void MainMenuState::handleInput()
	{
		sf::Event event;
		while (data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) data->window.close();
			if (data->input.isSpriteClicked(playButton, sf::Mouse::Left, data->window) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				data->machine.addState(StateRef(new GameState(data)), true);
			}
		}
	}

	void MainMenuState::update(float dt)
	{

	}

	void MainMenuState::draw(float dt)
	{
		data->window.clear();
		data->window.draw(backgroundSprite);
		data->window.draw(playButton);
		data->window.draw(title);
		data->window.display();
	}
}