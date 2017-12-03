#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
#include "Game.h"


namespace fb
{
	class MainMenuState :public State
	{
	public:
		MainMenuState(gameDataRef data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		gameDataRef data;

		sf::Sprite playButton;
		sf::Sprite title;
		sf::Sprite backgroundSprite;
	};
}