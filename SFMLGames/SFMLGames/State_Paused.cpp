#include "State_Paused.h"
#include "StateManager.h"

State_Paused::State_Paused(StateManager * pStateManager) : BaseState(pStateManager)
{

}

State_Paused::~State_Paused()
{
}

void State_Paused::onCreate()
{
	setTransparent(true);
	_font.loadFromFile("font/arial.ttf");
	_text.setFont(_font);
	_text.setString(sf::String("Paused"));
	_text.setCharacterSize(14);
	_text.setStyle(sf::Text::Bold);

	auto windowSize = _stateMgr->GetContext()->_wind->getRenderWindow()->getSize();

	auto textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	_rect.setSize(sf::Vector2f(windowSize));
	_rect.setPosition(0, 0);
	_rect.setFillColor(sf::Color(0, 0, 0, 150));

	auto eventManager = _stateMgr->GetContext()->_eventManager;
	eventManager->addCallback(StateType::Paused, "Key_P", &State_Paused::unpause, this);

}

void State_Paused::onDestroy()
{
	auto eventManager = _stateMgr->GetContext()->_eventManager;
	eventManager->removeCallback(StateType::Paused, "Key_P");
}

void State_Paused::activate()
{
	auto window = _stateMgr->GetContext()->_wind->getRenderWindow();
	window->draw(_rect);
	window->draw(_text);
}

void State_Paused::deactivate()
{
	_stateMgr->SwitchTo(StateType::Game);
}

void State_Paused::update(const sf::Time& pTime)
{
}

void State_Paused::draw()
{
}

void State_Paused::unpause(EventDetails* pDetails)
{
}
