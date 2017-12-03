#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
#include "DEFINITIONS.h"

namespace fb
{
	class Pipe
	{
	public:
		Pipe(gameDataRef data);
		void drawPipes();
		void spawnBottomPipe();
		void spawnTopPipe();
		void spawnScoringPipe();
		void movePipes(float dt);
		void randomisePipeOffset();

		const std::vector<sf::Sprite>& getPipeSprites() const;
		std::vector<sf::Sprite>& getScoringSprites();

	private:
		gameDataRef data;
		std::vector<sf::Sprite> pipeSprites;
		std::vector<sf::Sprite> scoringPipes;
		int landHeight;
		int pipeSpawnYOffset;
	};
}