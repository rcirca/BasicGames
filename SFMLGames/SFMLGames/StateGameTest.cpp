#include "StateGameTest.h"


StateGameTest::StateGameTest() : _window("TILTED", sf::Vector2u(800, 600)), _stateManager(&_context)
{
	_clock.restart();
	srand(time(nullptr));

	_context._wind = &_window;
	_context._eventManager = _window.getEventManager();
	_stateManager.switchTo(StateType::Intro);
}

StateGameTest::~StateGameTest()
{
	
}

sf::Time StateGameTest::getElapsed()
{
	return _clock.getElapsedTime();
}


void StateGameTest::restartClock()
{
	_elapsed = _clock.restart();
}

Window* StateGameTest::getWindow()
{
	return &_window;
}

void StateGameTest::update()
{
	_window.update();
	_stateManager.update(_elapsed);
}

void StateGameTest::render()
{
	_window.beginDraw();
	_stateManager.draw();
	_window.endDraw();
}

void StateGameTest::lateUpdate()
{
	_stateManager.processRequests();
	restartClock();
}


