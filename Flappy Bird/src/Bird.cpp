#include "Bird.h"

namespace fb
{
	Bird::Bird(gameDataRef _data) : data(_data)
	{
		animationIterator = 0;
		animationFrames.push_back(data->assets.getTexture("Bird Frame 1"));
		animationFrames.push_back(data->assets.getTexture("Bird Frame 2"));
		animationFrames.push_back(data->assets.getTexture("Bird Frame 3"));
		animationFrames.push_back(data->assets.getTexture("Bird Frame 4"));

		birdSprite.setTexture(data->assets.getTexture("Bird Frame 1"));

		birdSprite.setPosition(
			data->window.getSize().x / 4 - (birdSprite.getGlobalBounds().width / 2),
			data->window.getSize().y / 2 - (birdSprite.getGlobalBounds().height / 2)
		);

		birdState = BIRD_STATE_STILL;
		sf::Vector2f origin = sf::Vector2f(
			birdSprite.getGlobalBounds().width / 2, 
			birdSprite.getGlobalBounds().height
		);

		birdSprite.setOrigin(origin);
		rotation = 0;
	}

	void Bird::drawBird()
	{
		data->window.draw(birdSprite);
	}

	void Bird::animateBird(float dt)
	{
		if (clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / 4) //4 frames
		{
			if (animationIterator < 4 - 1) animationIterator++; //cuz we have 4 frames
			else animationIterator = 0;

			birdSprite.setTexture(animationFrames.at(animationIterator));
			clock.restart();
		}
	}

	void Bird::update(float dt)
	{
		if (birdState == BIRD_STATE_FALLING)
		{
			birdSprite.move(0, GRAVITY*dt);
			rotation += ROTATION_SPEED*dt;
			if (rotation > 15.0f) rotation = 15.0f;
			birdSprite.setRotation(rotation);
		}
		else if (birdState == BIRD_STATE_FLYING)
		{
			birdSprite.move(0, -FLYING_SPEED*dt);
			rotation -= ROTATION_SPEED*dt;
			if (rotation < -10.0f) rotation = -10.0f;
			birdSprite.setRotation(rotation);
		}

		if (movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
		{
			movementClock.restart();
			birdState = BIRD_STATE_FALLING;
		}
	}

	void Bird::tap()
	{
		movementClock.restart();
		birdState = BIRD_STATE_FLYING;
	}

	const sf::Sprite& Bird::getSprite() const
	{
		return birdSprite;
	}
}
