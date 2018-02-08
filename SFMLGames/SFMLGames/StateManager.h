#pragma once
#include <SFML/System.hpp>
#include "EventManager.h"
#include "Window.h"

enum class StateType
{
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};

struct SharedContext
{
	SharedContext() :_window(nullptr), _eventManager(nullptr){}
	Window* _window;
	EventManager* _eventManager;
};
class StateManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* pStateManager)
	: _stateManager(pStateManager), _transparent(false), _transcendent(false)
	{
		
	}
	virtual ~BaseState(){}

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& pTime) = 0;
	virtual void draw() = 0;

	void setTransparent(const bool& pTransparent)
	{
		_transparent = pTransparent;
	}

	bool isTransparent() const
	{
		return _transparent;
	}

	void setTranscendent(const bool& pTranscendent)
	{
		_transcendent = pTranscendent;
	}

	bool isTranscendent() const
	{
		return _transcendent;
	}

	StateManager* getStateManager()
	{
		return _stateManager;
	}

protected:
	StateManager* _stateManager;
	bool _transcendent;
	bool _transparent;
};