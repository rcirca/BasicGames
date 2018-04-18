#pragma once
#include "Window.h"
#include "EventManager.h"
struct SharedContext {
	SharedContext()
		:_wind(nullptr),
		_eventManager(nullptr) {}

	Window* _wind;
	EventManager* _eventManager;
};