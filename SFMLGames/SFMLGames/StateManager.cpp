#include "StateManager.h"

StateManager::StateManager(SharedContext * pShared) : _shared(pShared)
{
	RegisterState<State_Intro>(StateType::Intro);
	RegisterState<State_MainMenu>(StateType::MainMenu);
	RegisterState<State_Game>(StateType::Game);
	RegisterState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager()
{
	for (auto &itr : _states)
	{
		itr.second->onDestroy();
		delete itr.second;
	}
}

void StateManager::Update(const sf::Time & pTime)
{

}

void StateManager::Draw()
{
	if (_states.empty())
		return;

	if (_states.back().second->isTransparent()
		&& _states.size() > 1)
	{
		auto itr = _states.end();
		while (itr != _states.begin())
		{
			if (itr != _states.end())
			{
				if (!itr->second->isTransparent())
					break;
			}
			--itr;
		}

		for (; itr != _states.end(); ++itr)
			itr->second->draw();
	}
	else
		_states.back().second->draw();
}

void StateManager::ProcessRequests()
{
}

SharedContext * StateManager::GetContext()
{
	return nullptr;
}

bool StateManager::HasState(const StateType & pType)
{
	return false;
}

void StateManager::SwitchTo(const StateType & pType)
{
}

void StateManager::Remove(const StateType & pType)
{
}

void StateManager::CreateState(const StateType & pType)
{
}

void StateManager::RemoveState(const StateType & pType)
{
}
