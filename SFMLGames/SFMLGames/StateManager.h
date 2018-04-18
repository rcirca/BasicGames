#pragma once
#include "EventManager.h"
#include "SharedContext.h"
#include "BaseState.h"

enum class StateType
{
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};


using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager 
{
public:
	StateManager(SharedContext* pShared);
	~StateManager();

	void Update(const sf::Time& pTime);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& pType);

	void SwitchTo(const StateType& pType);
	void Remove(const StateType& pType);

private:
	// Methods.
	void CreateState(const StateType& pType);
	void RemoveState(const StateType& pType);

	template<class T>
	void RegisterState(const StateType& pType) {
		m_stateFactory[pTtype] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}

	// Members.
	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};