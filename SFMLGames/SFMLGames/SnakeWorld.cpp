#include "SnakeWorld.h"


SnakeWorld::SnakeWorld(sf::Vector2u pWindowSize)
{
	_blockSize = 16;
	_windowSize = pWindowSize;
	respawnApple();
	_appleShape.setFillColor(sf::Color::Red);
	_appleShape.setRadius(_blockSize / 2);

	for (int i = 0; i < 4; ++i)
	{
		_bounds[i].setFillColor(sf::Color::Red);
		if (!((i + 1) % 2))
			_bounds[i].setSize(sf::Vector2f(_windowSize.x, _blockSize));
		else
			_bounds[i].setSize(sf::Vector2f(_blockSize, _windowSize.y));

		if (i < 2)
			_bounds[i].setPosition(0, 0);
		else
		{
			_bounds[i].setOrigin(_bounds[i].getSize());
			_bounds[i].setPosition(sf::Vector2f(_windowSize));
		}

	}
}

SnakeWorld::~SnakeWorld()
{
	
}

void SnakeWorld::draw(sf::RenderWindow& pRenderWindow) const
{
	for (int i = 0; i < 4; ++i)
		pRenderWindow.draw(_bounds[i]);

	pRenderWindow.draw(_appleShape);
}

int SnakeWorld::getBlockSize() const
{
	return _blockSize;
}

void SnakeWorld::respawnApple()
{
	auto maxX = (_windowSize.x / _blockSize) - 2;
	auto maxY = (_windowSize.y / _blockSize) - 2;
	_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	_appleShape.setPosition(_item.x * _blockSize, _item.y * _blockSize);
}

void SnakeWorld::update(Snake& pPlayer)
{
	if(pPlayer.getPosition() == _item)
	{
		pPlayer.extend();
		pPlayer.increaseScore();
		respawnApple();
	}

	if (checkOutOfBounds(pPlayer))
		pPlayer.lose();
}

bool SnakeWorld::checkOutOfBounds(Snake& pPlayer) const
{
	int gridSizeX = _windowSize.x / _blockSize;
	int gridSizeY = _windowSize.y / _blockSize;
	return pPlayer.getPosition().x <= 0 ||
		pPlayer.getPosition().y <= 0 ||
		pPlayer.getPosition().x >= gridSizeX - 1 ||
		pPlayer.getPosition().y >= gridSizeY - 1;
}





