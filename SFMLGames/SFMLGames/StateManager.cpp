#include "StateManager.h"

StateManager::StateManager(SharedContext * pShared) : m_shared(pShared)
{
}

StateManager::~StateManager()
{
}

void StateManager::Update(const sf::Time & pTime)
{
}

void StateManager::Draw()
{
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
