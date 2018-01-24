#pragma once
#include "Window.h"
#include <SFML/Graphics.hpp>

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

	Window _window;
	sf::Clock _clock;
	sf::Time _elapsedTime;
};
