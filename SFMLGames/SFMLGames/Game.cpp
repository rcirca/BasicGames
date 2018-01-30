#include "Game.h"

Game::Game() : _snakeWorld(sf::Vector2u(800,600)), 
_snake(_snakeWorld.getBlockSize()), 
_window("SNEK", sf::Vector2u(800, 600))
{
	restartClock();
	srand(time(nullptr));
	_elapsedTime = 0.0f;
}

Game::~Game()
{
	
}


void Game::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& _snake.getExactDirection() != Direction::Down) {
		_snake.setDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& _snake.getExactDirection() != Direction::Up) {
		_snake.setDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& _snake.getExactDirection() != Direction::Right) {
		_snake.setDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& _snake.getExactDirection() != Direction::Left) {
		_snake.setDirection(Direction::Right);
	}
}

void Game::update()
{
	_window.update();
	float timeStep = 1.0f / _snake.getSpeed();
	if(_elapsedTime >= timeStep)
	{
		_snake.tick();
		_snakeWorld.update(_snake);
		_elapsedTime -= timeStep;
		if (_snake.hasLost())
			_snake.reset();
	}
}

void Game::render()
{
	_window.beginDraw();
	_snakeWorld.draw(*_window.getRenderWindow());
	_snake.draw(*_window.getRenderWindow());
	_window.endDraw();
}

Window* Game::getWindow()
{
	return &_window;
}

sf::Time Game::getElapsed() const
{
	return _clock.getElapsedTime();
}


void Game::restartClock()
{
	_elapsedTime += _clock.restart().asSeconds();
}