#include "Game.h"
#include "StateManager.h"
Game::Game() : _snakeWorld(sf::Vector2u(800,600)), 
_snake(_snakeWorld.getBlockSize(), &_textBox), 
_window("SNEK", sf::Vector2u(800, 600))
{
	restartClock();
	srand(time(nullptr));
	_elapsedTime = 0.0f;
	_textBox.setup(5, 14, 350, sf::Vector2f(225, 0));
	_textBox.add("Seeded random number generator with " + std::to_string(time(NULL)));
	_textBox.add("Score: " + std::to_string(_snake.getScore()));

	_window.getEventManager()->addCallback(StateType::Game, "MoveUp", &Game::handleInput, this);
	_window.getEventManager()->addCallback(StateType::Game, "MoveDown", &Game::handleInput, this);
	_window.getEventManager()->addCallback(StateType::Game, "MoveLeft", &Game::handleInput, this);
	_window.getEventManager()->addCallback(StateType::Game, "MoveRight", &Game::handleInput, this);

}

Game::~Game()
{
	
}


void Game::handleInput(EventDetails* pDetails)
{
	if (pDetails->_name.compare("MoveUp") == 0
		&& _snake.getExactDirection() != Direction::Down) {
		_snake.setDirection(Direction::Up);
	}
	else if (pDetails->_name.compare("MoveDown") == 0
		&& _snake.getExactDirection() != Direction::Up) {
		_snake.setDirection(Direction::Down);
	}
	else if (pDetails->_name.compare("MoveLeft") == 0
		&& _snake.getExactDirection() != Direction::Right) {
		_snake.setDirection(Direction::Left);
	}
	else if (pDetails->_name.compare("MoveRight") == 0
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
	_textBox.draw(*_window.getRenderWindow());
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