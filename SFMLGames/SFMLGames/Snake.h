#pragma once
#include <SFML/Graphics.hpp>
struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x,y){ }
	sf::Vector2i position;
};


using SnakeContainer = std::vector<SnakeSegment>;

enum Direction{None, Up, Down, Left, Right};
class Snake
{
public:
	Snake(int pBlockSize);
	~Snake();

	void setDirection(Direction pDirection);
	Direction getDirection() const;
	int getSpeed() const;
	sf::Vector2i getPosition();
	int getLives() const;
	int getScore() const;
	void increaseScore();
	bool hasLost() const;

	void lose();
	void toggleLost();

	void extend();
	void reset();

	void move();
	void tick();
	void cut(int pSegments);
	
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

