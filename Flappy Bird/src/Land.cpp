#include "Land.h"

#include "DEFINITIONS.h"

namespace fb
{
	Land::Land(gameDataRef _data) : data(_data)
	{
		sf::Sprite sprite(data->assets.getTexture("Land"));
		sf::Sprite sprite2(data->assets.getTexture("Land"));

		sprite.setPosition(0, data->window.getSize().y - sprite.getGlobalBounds().height);
		sprite2.setPosition(sprite.getGlobalBounds().width, data->window.getSize().y - sprite.getGlobalBounds().height);

		landSprites.push_back(sprite);
		landSprites.push_back(sprite2);
	}

	void Land::moveLand(float dt)
	{
		for (unsigned short int i = 0; i < landSprites.size(); ++i)
		{
			float movement = PIPE_MOVEMENT_SPEED*dt;
			landSprites.at(i).move(-movement, 0.0f);
			if (landSprites.at(i).getPosition().x < 0 - landSprites.at(i).getGlobalBounds().width)
			{
				sf::Vector2f position(data->window.getSize().x, landSprites.at(i).getPosition().y);
				landSprites.at(i).setPosition(position);
			}
		}
	}

	void Land::drawLand()
	{
		for (unsigned short int i = 0; i < landSprites.size(); ++i)
		{
			data->window.draw(landSprites.at(i));
		}
	}

	const std::vector<sf::Sprite>& Land::getSprites() const
	{
		return landSprites;
	}
}