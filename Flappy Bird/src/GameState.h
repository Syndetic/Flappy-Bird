#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"

namespace fb
{
	class GameState :public State
	{
	public:
		GameState(gameDataRef data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		gameDataRef data;

		sf::Sprite backgroundSprite;
		sf::Clock clock;
		Pipe *pipe;
		Land *land;
		Bird *bird;
		Collision collision;
		Flash *flash;

		int gameState;
		int score;
		sf::Text text_score;
		sf::Font arial;
		void drawScore();
	};
}