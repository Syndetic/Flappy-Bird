#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINITIONS.h"
#include <vector>

namespace fb
{
	class Bird
	{
	public:
		Bird(gameDataRef _data);

		void drawBird();
		void animateBird(float dt);
		void update(float dt);
		void tap();
		const sf::Sprite& getSprite() const;

	private:
		gameDataRef data;
		sf::Sprite birdSprite;

		sf::Clock clock;
		std::vector<sf::Texture> animationFrames;
		unsigned int animationIterator;

		sf::Clock movementClock;
		int birdState;
		float rotation;
	};
}