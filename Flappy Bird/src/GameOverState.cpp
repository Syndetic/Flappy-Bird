#include <sstream> 
#include <iostream>

#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "InputManager.h"

namespace fb
{
	GameOverState::GameOverState(gameDataRef data, int _score) : data(data), score(_score) { }

	int GameOverState::highscore = -1;

	void GameOverState::init()
	{
		data->assets.loadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		data->assets.loadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		data->assets.loadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
		data->assets.loadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
		data->assets.loadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
		data->assets.loadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
		data->assets.loadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);

		backgroundSprite.setTexture(this->data->assets.getTexture("Game Over Background"));
		gameOverTitle.setTexture(this->data->assets.getTexture("Game Over Title"));
		gameOverBody.setTexture(this->data->assets.getTexture("Game Over Body"));
		retryButton.setTexture(this->data->assets.getTexture("Play Button"));

		gameOverBody.setPosition(
			data->window.getSize().x / 2 - gameOverBody.getGlobalBounds().width / 2,
			data->window.getSize().y / 2 - gameOverBody.getGlobalBounds().height / 2
		);

		gameOverTitle.setPosition(
			data->window.getSize().x / 2 - gameOverTitle.getGlobalBounds().width / 2,
			gameOverBody.getPosition().y - (gameOverTitle.getGlobalBounds().height*1.2)
		);

		retryButton.setPosition(
			data->window.getSize().x / 2 - retryButton.getGlobalBounds().width / 2,
			gameOverBody.getPosition().y + gameOverBody.getGlobalBounds().height + retryButton.getGlobalBounds().height*0.2
		);

		scoreText.setFont(data->assets.getFont("Flappy Font"));
		scoreText.setString(std::to_string(score));
		scoreText.setCharacterSize(56);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(data->window.getSize().x / 10 * 7.1, data->window.getSize().y / 2.27);

		if (score > highscore) highscore = score;
		if (score >= PLATINUM_MEDAL_SCORE) medal.setTexture(data->assets.getTexture("Platinum Medal"));
		else if (score >= GOLD_MEDAL_SCORE) medal.setTexture(data->assets.getTexture("Gold Medal"));
		else if (score >= SILVER_MEDAL_SCORE) medal.setTexture(data->assets.getTexture("Silver Medal"));
		else if (score >= BRONZE_MEDAL_SCORE) medal.setTexture(data->assets.getTexture("Bronze Medal"));

		medal.setPosition(175, 465);

		highscoreText.setFont(data->assets.getFont("Flappy Font"));
		highscoreText.setString(std::to_string(highscore));
		highscoreText.setCharacterSize(56);
		highscoreText.setFillColor(sf::Color::White);
		highscoreText.setPosition(data->window.getSize().x / 10 * 7.1, data->window.getSize().y / 1.87);

	}

	void GameOverState::handleInput()
	{
		sf::Event event;
		while (data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) data->window.close();
			if (data->input.isSpriteClicked(retryButton, sf::Mouse::Left, data->window) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				data->machine.addState(StateRef(new GameState(data)), true);
			}
		}
	}

	void GameOverState::update(float dt)
	{

	}

	void GameOverState::draw(float dt)
	{
		data->window.clear();
		data->window.draw(backgroundSprite);
		data->window.draw(gameOverBody);
		data->window.draw(gameOverTitle);
		data->window.draw(retryButton);
		data->window.draw(scoreText);
		data->window.draw(highscoreText);
		data->window.draw(medal);
		data->window.display();
	}
}