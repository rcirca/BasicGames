#include "StateManager.h"

StateManager::StateManager(SharedContext* pShared) : _shared(pShared)
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

void StateManager::Update(const sf::Time& pTime)
{
	if (_states.empty())
		return;

	if (_states.back().second->isTranscendent() && _states.size() > 1)
	{
		auto itr = _states.end();

		while (itr != _states.begin())
		{
			if (itr != _states.end())
			{
				if (!itr->second->isTranscendent)
					break;
			}
			--itr;
		}
		for (; itr != _states.end(); ++itr)
			itr->second->update(pTime);
	}
	else
		_states.back().second->update(pTime);
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
	while (_toRemove.begin() != _toRemove.end())
	{
		RemoveState(*_toRemove.begin());
		_toRemove.erase(_toRemove.begin());
	}
}

SharedContext* StateManager::GetContext()
{
	return _shared;
}

bool StateManager::HasState(const StateType & pType)
{
	for (auto itr = _states.begin(); itr != _states.end(); ++itr)
	{
		if (itr->first == pType)
		{
			auto removed = std::find(_toRemove.begin(), _toRemove.end(), pType);
			if (removed == _toRemove.end())
				return true;

			return false;
		}
	}
	return false;
}

void StateManager::SwitchTo(const StateType & pType)
{
	_shared->_eventManager->setCurrentState(pType);

	for (auto itr = _states.begin(); itr != _states.end(); ++itr)
	{
		if (itr->first == pType)
		{
			_states.back().second->deactivate();
			StateType tmpType = itr->first;
			BaseState* tmpState = itr->second;
			_states.erase(itr);
			_states.emplace_back(tmpType, tmpState);
			tmpState->activate();
			return;
		}
	}
	
	if (!_states.empty())
		_states.back().second->deactivate();

	CreateState(pType);
	_states.back().second->activate();
}

void StateManager::Remove(const StateType & pType)
{
	_toRemove.push_back(pType);
}

void StateManager::CreateState(const StateType & pType)
{
	auto newState = _stateFactory.find(pType);
	if (newState == _stateFactory.end())
		return;

	auto state = newState->second();
	_states.emplace_back(pType, state);
	state->onCreate();
}

void StateManager::RemoveState(const StateType & pType)
{
	for (auto itr = _states.begin(); itr != _states.end(); ++itr)
	{
		if (itr->first == pType)
		{
			itr->second->onDestroy();
			delete itr->second;
			_states.erase(itr);
			return;
		}
	}
}
