#include "Game.h"

Game::Game() : _window("Some Setup", sf::Vector2u(800, 600))
{
	restartClock();
}

Game::~Game()
{
	
}


void Game::handleInput()
{
	
}

void Game::update()
{
	_window.update();
}

void Game::render()
{
	_window.beginDraw();

	_window.endDraw();
}

Window* Game::getWindow()
{
	return &_window;
}

sf::Time Game::getElapsed() const
{
	return _elapsedTime;
}


void Game::restartClock()
{
	_elapsedTime = _clock.restart();
}







