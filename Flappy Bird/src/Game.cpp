#include "Game.h"
#include "MainMenuState.h"
#include <time.h>
namespace fb
{
	Game::Game(unsigned int width, unsigned int height, std::string title)
	{
		data->window.create(
			sf::VideoMode(width, height), 
			title, 
			sf::Style::Close | sf::Style::Titlebar
		);
		data->window.setIcon(icon32x32.width, icon32x32.height, icon32x32.pixel_data);
		data->window.setFramerateLimit(60);
		

		data->machine.addState(StateRef(new MainMenuState(this->data)));

		srand(time(NULL));
		this->run();
	}

	void Game::run()
	{
		float newTime, frameTime, interpolation;
		float currentTime = clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->data->window.isOpen())
		{
			newTime = this->clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;
			currentTime = newTime;

			accumulator += frameTime;
			
			this->data->machine.processStateChanges();
			while (accumulator >= dt)
			{
				this->data->machine.getActiveState()->handleInput();
				this->data->machine.getActiveState()->update(dt);
				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->data->machine.getActiveState()->draw(interpolation);
		}
	}
}