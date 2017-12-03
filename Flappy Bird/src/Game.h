#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "icon.h"

namespace fb
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> gameDataRef;

	class Game
	{
	public:
		Game(unsigned int width, unsigned int height, std::string title);

	private:
		const float dt = 1.0f / 60.0f; //how many times we want to update per second
		sf::Clock clock;

		gameDataRef data = std::make_shared<GameData>();

		void run();
	};
}