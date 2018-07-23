#include "StateManager.h"

StateManager::StateManager(SharedContext* pShared) : _shared(pShared)
{
	registerState<State_Intro>(StateType::Intro);
	registerState<State_MainMenu>(StateType::MainMenu);
	registerState<State_Game>(StateType::Game);
	registerState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager()
{
	for (auto &itr : _states)
	{
		itr.second->onDestroy();
		delete itr.second;
	}
}

void StateManager::update(const sf::Time& pTime)
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
				if (!itr->second->isTranscendent())
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

void StateManager::draw()
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
		{
			_shared->_wind->getRenderWindow()->setView(itr->second->getView());
			itr->second->draw();
		}
	}
	else
		_states.back().second->draw();
}

void StateManager::processRequests()
{
	while (_toRemove.begin() != _toRemove.end())
	{
		removeState(*_toRemove.begin());
		_toRemove.erase(_toRemove.begin());
	}
}

SharedContext* StateManager::getContext()
{
	return _shared;
}

bool StateManager::hasState(const StateType & pType)
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

void StateManager::switchTo(const StateType & pType)
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
			_shared->_wind->getRenderWindow()->setView(tmpState->getView());
			return;
		}
	}
	
	if (!_states.empty())
		_states.back().second->deactivate();

	createState(pType);
	_states.back().second->activate();
	_shared->_wind->getRenderWindow()->setView(_states.back().second->getView());
}

void StateManager::remove(const StateType & pType)
{
	_toRemove.push_back(pType);
}

void StateManager::createState(const StateType & pType)
{
	auto newState = _stateFactory.find(pType);
	if (newState == _stateFactory.end())
		return;

	auto state = newState->second();
	state->_view = _shared->_wind->getRenderWindow()->getDefaultView();
	_states.emplace_back(pType, state);
	state->onCreate();
}

void StateManager::removeState(const StateType & pType)
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

