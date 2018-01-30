#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class SnakeWorld
{
public:
	SnakeWorld(sf::Vector2u pWindowSize);
	~SnakeWorld();

	int getBlockSize() const;
	void respawnApple();
	void update(Snake& pPlayer);;
	void draw(sf::RenderWindow& pRenderWindow) const;

private:
	bool checkOutOfBounds(Snake& pPlayer) const;
	sf::Vector2u _windowSize;
	sf::Vector2i _item;
	int _blockSize;
	sf::CircleShape _appleShape;
	sf::RectangleShape _bounds[4];
};
