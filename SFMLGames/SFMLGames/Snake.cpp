#include "Snake.h"

Snake::Snake(int pBlockSize)
{
}

Snake::~Snake()
{
}

void Snake::setDirection(Direction pDirection)
{
	_direction = pDirection;
}

Direction Snake::getDirection()
{
	return _direction;
}

int Snake::getSpeed()
{
	return _speed;
}

sf::Vector2i Snake::getPosition()
{
	return sf::Vector2i();
}

int Snake::getLives()
{
	return _lives;
}

int Snake::getScore()
{
	return _score;
}

void Snake::increaseScore()
{
	_score += 100;
}

bool Snake::hasLost()
{
	return _lost;
}

void Snake::lose()
{
}

void Snake::toggleLost()
{
}

void Snake::extend()
{
}

void Snake::reset()
{
}

void Snake::move()
{
}

void Snake::tick()
{
}

void Snake::cut()
{
}

void Snake::draw(sf::RenderWindow pRenderWindow)
{
}

void Snake::checkCollision()
{
}
