#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class BaseState {
	friend class StateManager;
public:
	BaseState(StateManager* pStateManager) :_stateMgr(pStateManager),
		_transparent(false), _transcendent(false) {}
	virtual ~BaseState() {}

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update(const sf::Time& pTime) = 0;
	virtual void Draw() = 0;

	void SetTransparent(const bool& pTransparent) { _transparent = pTransparent; }
	bool IsTransparent()const { return _transparent; }
	void SetTranscendent(const bool& pTranscendence) { _transcendent = pTranscendence; }
	bool IsTranscendent()const { return _transcendent; }
	StateManager* GetStateManager() { return _stateMgr; }

protected:
	StateManager* _stateMgr;
	bool _transparent;
	bool _transcendent;
};