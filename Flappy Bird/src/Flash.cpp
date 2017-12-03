#include "Flash.h"

namespace fb
{
	Flash::Flash(gameDataRef _data) : data(_data)
	{
		shape = sf::RectangleShape(sf::Vector2f(data->window.getSize()));
		shape.setFillColor(sf::Color(255, 255, 255, 0));
		flashOn = true;
	}

	void Flash::show(float dt)
	{
		if (flashOn)
		{
			int alpha = (int)shape.getFillColor().a + FLASH_SPEED*dt;
			if (alpha >= 255.0f)
			{
				flashOn = false;
				alpha = 255.0f;
			}
			shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
		else
		{
			int alpha = (int)shape.getFillColor().a - FLASH_SPEED*dt;
			if (alpha <= 0.0f)
			{
				flashOn = false;
				alpha = 0.0f;
			}
			shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
	}

	void Flash::draw()
	{
		data->window.draw(shape);
	}
}