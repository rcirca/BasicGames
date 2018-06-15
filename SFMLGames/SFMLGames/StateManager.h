#pragma once
#include "EventManager.h"
#include "SharedContext.h"
#include "BaseState.h"
#include "State_Main.h"
#include "State_Intro.h"
#include "State_Game.h"
#include "State_Paused.h"

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

	void update(const sf::Time& pTime);
	void draw();

	void processRequests();

	SharedContext* getContext();
	bool hasState(const StateType& pType);

	void switchTo(const StateType& pType);
	void remove(const StateType& pType);

private:
	// Methods.
	void createState(const StateType& pType);
	void removeState(const StateType& pType);

	template<class T>
	void registerState(const StateType& pType)
	{
		_stateFactory[pType] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}


	// Members.
	SharedContext* _shared;
	StateContainer _states;
	TypeContainer _toRemove;
	StateFactory _stateFactory;
};
