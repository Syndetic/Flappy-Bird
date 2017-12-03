#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>

namespace fb
{
	class Land
	{
	public:
		Land(gameDataRef data);
		
		void moveLand(float dt);
		void drawLand();
		const std::vector<sf::Sprite>& getSprites() const;

	private:
		gameDataRef data;
		std::vector<sf::Sprite> landSprites;
	};
}