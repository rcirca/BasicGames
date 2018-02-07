#pragma once
#include "Window.h"
#include "EventManager.h"
#include <iostream>

class GameMushroom {
public:
	GameMushroom();
	~GameMushroom();

	void update();
	void render();

	sf::Time getElapsed();
	void restartClock();

	void moveSprite(EventDetails* l_details);

	Window* getWindow();
private:
	Window _window;
	sf::Clock _clock;

	sf::Texture _texture;
	sf::Sprite _sprite;
};