#pragma once
#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "SharedContext.h"
#include <iostream>

class StateGameTest
{
public:
	StateGameTest();
	~StateGameTest();

	void update();
	void render();
	void lateUpdate();

	sf::Time getElapsed();
	Window* getWindow();

private:
	void restartClock();

	SharedContext _context;
	Window _window;
	StateManager _stateManager;
	sf::Clock _clock;
	sf::Time _elapsed;
};