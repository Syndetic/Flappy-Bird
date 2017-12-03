#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINITIONS.h"

namespace fb
{
	class Flash
	{
	public:
		Flash(gameDataRef _data);

		void show(float dt);
		void draw();

	private:
		gameDataRef data;

		sf::RectangleShape shape;

		bool flashOn;
	};
}