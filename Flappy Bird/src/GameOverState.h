#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
#include "Game.h"
#include "GameState.h"


namespace fb
{
	class GameOverState :public State
	{
	public:
		GameOverState(gameDataRef data, int _score);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

		static int highscore;

	private:
		gameDataRef data;

		sf::Sprite backgroundSprite;
		sf::Sprite gameOverTitle;
		sf::Sprite gameOverBody;
		sf::Sprite retryButton;

		sf::Sprite medal;

		sf::Text scoreText;
		sf::Text highscoreText;

		int score;
	};
}