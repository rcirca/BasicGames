#pragma once
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "SnakeWorld.h"

class Game
{
public:
	Game();
	~Game();

	sf::Time getElapsed() const;
	void restartClock();
	void handleInput();
	void update();
	void render();
	Window* getWindow();

private:

	SnakeWorld _snakeWorld;
	Snake _snake;
	Window _window;
	sf::Clock _clock;
	float _elapsedTime;
};
