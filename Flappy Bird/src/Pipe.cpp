#include "Pipe.h"
#include <iostream>

namespace fb
{
	Pipe::Pipe(gameDataRef data) : data(data) 
	{
		landHeight = data->assets.getTexture("Land").getSize().y; 
		pipeSpawnYOffset = 0;
	}

	void Pipe::drawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); ++i)
		{
			data->window.draw(pipeSprites.at(i));
		}
	}

	void Pipe::spawnBottomPipe()
	{
		sf::Sprite sprite(data->assets.getTexture("Pipe Up"));
		sprite.setPosition(
			data->window.getSize().x,
			data->window.getSize().y - sprite.getGlobalBounds().height - pipeSpawnYOffset
		);
		pipeSprites.push_back(sprite);
	}

	void Pipe::spawnTopPipe()
	{
		sf::Sprite sprite(data->assets.getTexture("Pipe Down"));
		sprite.setPosition(data->window.getSize().x, -pipeSpawnYOffset);
		pipeSprites.push_back(sprite);
	}

	void Pipe::movePipes(float dt)
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); ++i)
		{
			if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getGlobalBounds().width)
			{
				pipeSprites.erase(pipeSprites.begin() + i);
			}
			else 
			{
				float movement = PIPE_MOVEMENT_SPEED * dt;
				pipeSprites.at(i).move(-movement, 0);
			}
		}

		for (unsigned short int i = 0; i < scoringPipes.size(); ++i)
		{
			if (scoringPipes.at(i).getPosition().x < 0 - scoringPipes.at(i).getGlobalBounds().width)
			{
				scoringPipes.erase(scoringPipes.begin() + i);
			}
			else {
				float movement = PIPE_MOVEMENT_SPEED * dt;
				scoringPipes.at(i).move(-movement, 0);
			}
		}
	}

	void Pipe::randomisePipeOffset()
	{
		pipeSpawnYOffset = rand() % (landHeight + 1);
	}

	const std::vector<sf::Sprite>& Pipe::getPipeSprites() const
	{
		return pipeSprites;
	}

	void Pipe::spawnScoringPipe()
	{
		sf::Sprite sprite(data->assets.getTexture("Scoring Pipe"));
		sprite.setPosition(data->window.getSize().x + sprite.getGlobalBounds().width, 0);
		sprite.setColor(sf::Color(0, 0, 0, 0));
		scoringPipes.push_back(sprite);	
	}

	std::vector<sf::Sprite>& Pipe::getScoringSprites()
	{
		return scoringPipes;
	}
}