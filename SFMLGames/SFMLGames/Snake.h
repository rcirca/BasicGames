#pragma once
#include <SFML/Graphics.hpp>
struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x,y){ }
	sf::Vector2f position;
};


using SnakeContainer = std::vector<SnakeSegment>;

enum Direction{None, Up, Down, Left, Right};
class Snake
{
public:
	Snake(int pBlockSize);
	~Snake();

	void setDirection(Direction pDirection);
	Direction getDirection();
	int getSpeed();
	sf::Vector2i getPosition();
	int getLives();
	int getScore();
	void increaseScore();
	bool hasLost();
	void lose();
	void toggleLost();


	
};

