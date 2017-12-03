#include <sstream> 
#include <iostream>

#include "GameState.h"
#include "DEFINITIONS.h"
#include "InputManager.h"
#include "GameOverState.h"


namespace fb
{
	GameState::GameState(gameDataRef data) : data(data) { }

	void GameState::init()
	{
		data->assets.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		data->assets.loadTexture("Pipe Up", PIPE_UP_FILEPATH);
		data->assets.loadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		data->assets.loadTexture("Land", LAND_FILEPATH);
		data->assets.loadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		data->assets.loadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		data->assets.loadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		data->assets.loadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		data->assets.loadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		data->assets.loadFont("Flappy Font", FLAPPY_FONT);

		pipe = new Pipe(data);
		land = new Land(data);
		bird = new Bird(data);
		flash = new Flash(data);

		backgroundSprite.setTexture(this->data->assets.getTexture("Game Background"));
		text_score.setFont(this->data->assets.getFont("Flappy Font"));
		text_score.setCharacterSize(64);
		score = 0;
		gameState = GameStates::Ready;
	}

	void GameState::handleInput()
	{
		sf::Event event;
		while (data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) data->window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (gameState != GameStates::GameOver)
				{
					gameState = GameStates::Playing;
					bird->tap();
				}
			}
		}
	}

	void GameState::update(float dt)
	{
		if (gameState != GameStates::GameOver)
		{
			bird->animateBird(dt);

			land->moveLand(dt);
		}

		if (gameState == GameStates::Playing)
		{
			pipe->movePipes(dt);
			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				pipe->randomisePipeOffset();
				pipe->spawnBottomPipe();
				pipe->spawnTopPipe();
				pipe->spawnScoringPipe();

				clock.restart();
			}

			bird->update(dt);

			std::vector<sf::Sprite> landSprites = land->getSprites();
			for (unsigned short int i = 0; i < landSprites.size(); ++i)
			{
				if (collision.checkSpriteCollision(
					bird->getSprite(), 0.7f, 
					landSprites.at(i), 1.0f))
				{
					gameState = GameStates::GameOver;

					clock.restart();
				}
			}

			std::vector<sf::Sprite> pipeSprites = pipe->getPipeSprites();
			for (unsigned short int i = 0; i < pipeSprites.size(); ++i)
			{
				if (collision.checkSpriteCollision(
					bird->getSprite(), 0.625f, 
					pipeSprites.at(i), 1.0f))
				{
					gameState = GameStates::GameOver;

					clock.restart();
				}
			}

			if (GameStates::Playing == gameState)
			{
				std::vector<sf::Sprite>& scoringSprites = pipe->getScoringSprites();
				for (unsigned short int i = 0; i < scoringSprites.size(); ++i)
				{
					if (collision.checkSpriteCollision(
						bird->getSprite(), 0.625f,
						scoringSprites.at(i), 1.0f))
					{
						score++;
						std::cout << score << std::endl;
						scoringSprites.erase(scoringSprites.begin() + i);
					}
				}
			}
		}

		if (gameState == GameStates::GameOver)
		{
			flash->show(dt);
			
			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				data->machine.addState(StateRef(new GameOverState(data, score)), true);
			}
		}
	}

	void GameState::drawScore()
	{
		std::ostringstream buff;
		buff << "Score: " << score;

		text_score.setString(buff.str());
		data->window.draw(text_score);
	}

	void GameState::draw(float dt)
	{
		data->window.clear();
		data->window.draw(backgroundSprite);
		pipe->drawPipes();
		land->drawLand();
		bird->drawBird();
		drawScore();
		flash->draw();
		data->window.display();
	}
}