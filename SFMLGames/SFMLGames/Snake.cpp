#include "Snake.h"

Snake::Snake(int pBlockSize)
{
	_size = pBlockSize;
	_rectangeBody.setSize(sf::Vector2f(_size - 1, _size - 1));
	reset();
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
	return !_snakeBody.empty() ? _snakeBody.front().position : sf::Vector2i(1, 1);
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
	_lost = true;
}

void Snake::toggleLost()
{
	_lost = !_lost;
}

void Snake::extend()
{
	if (_snakeBody.empty())
		return;

	auto& tailHead = _snakeBody[_snakeBody.size() - 1];

	if (_snakeBody.size() > 1)
	{
		auto& tailBone = _snakeBody[_snakeBody.size() - 2];
		if (tailHead.position.x == tailBone.position.x)
		{
			if (tailHead.position.y > tailBone.position.y)
				_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
			else
				_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
		}
		else if (tailHead.position.y == tailBone.position.y) 
		{
			if (tailHead.position.x > tailBone.position.x)
				_snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
			else
				_snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
		}
	}
	else
	{
		if (_direction == Direction::Up)
			_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
		else if (_direction == Direction::Down)
			_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
		else if (_direction == Direction::Left)
			_snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
		else if (_direction == Direction::Right)
			_snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
	}
}

void Snake::reset()
{
	_snakeBody.clear();

	_snakeBody.push_back(SnakeSegment(5, 7));
	_snakeBody.push_back(SnakeSegment(5, 6));
	_snakeBody.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);
	_speed = 15;
	_lives = 3;
	_score = 0;
	_lost = false;
}

void Snake::move()
{
	for (int i = _snakeBody.size() - 1; i > 0; i--)
		_snakeBody[i].position = _snakeBody[i - 1].position;

	switch (_direction) 
	{
		case Direction::Left:
			--_snakeBody[0].position.x;
			break;
		case Direction::Right:
			++_snakeBody[0].position.x;
			break;
		case Direction::Up:
			--_snakeBody[0].position.y;
			break;
		case Direction::Down:
			++_snakeBody[0].position.y;
			break;
	}
}

void Snake::tick()
{
	if (_snakeBody.empty())
		return;

	if (_direction == Direction::None)
		return;

	move();
	checkCollision();
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
