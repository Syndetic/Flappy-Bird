#include "InputManager.h"

namespace fb
{
	bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect tempRectangle(
				object.getPosition().x,
				object.getPosition().y,
				object.getGlobalBounds().width,
				object.getGlobalBounds().height
			);

			if (tempRectangle.contains(sf::Mouse::getPosition(window))) return true;
			else return false;
		}
	}


	sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &window)
	{
		return sf::Mouse::getPosition(window);
	}
}