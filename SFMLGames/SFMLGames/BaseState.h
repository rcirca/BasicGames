#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class BaseState {
	friend class StateManager;
public:
	BaseState(StateManager* pStateManager) :_stateMgr(pStateManager),
		_transparent(false), _transcendent(false) {}
	virtual ~BaseState() {}

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& pTime) = 0;
	virtual void draw() = 0;

	void setTransparent(const bool& pTransparent) { _transparent = pTransparent; }
	bool isTransparent()const { return _transparent; }
	void setTranscendent(const bool& pTranscendence) { _transcendent = pTranscendence; }
	bool isTranscendent()const { return _transcendent; }
	StateManager* getStateManager() { return _stateMgr; }

protected:
	StateManager* _stateMgr;
	bool _transparent;
	bool _transcendent;
};