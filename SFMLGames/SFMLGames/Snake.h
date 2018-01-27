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

	void extend();
	void reset();

	void move();
	void tick();
	void cut();
	
	void draw(sf::RenderWindow pRenderWindow);

private:
	void checkCollision();
	
	sf::RectangleShape _rectangeBody;
	SnakeContainer _snakeBody;
	Direction _direction;
	int _size;
	int _speed;
	int _lives;
	int _score;
	bool _lost;
};

