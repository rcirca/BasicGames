#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager* pStateManager) : BaseState(pStateManager)
{
	
}

State_Intro::~State_Intro()
{
	
}

void State_Intro::onCreate()
{
	_timePassed = 0.0f;

	auto windowSize = _stateMgr->GetContext()->_wind->getRenderWindow()->getSize();

	_introTexture.loadFromFile("intro.png");
	_introSprite.setTexture(_introTexture);
	_introSprite.setOrigin(_introTexture.getSize().x / 2.0f, _introTexture.getSize().y / 2.0f);

	_introSprite.setPosition(windowSize.x / 2.0f, 0);

	_font.loadFromFile("arial.ttf");
	_text.setFont(_font);
	_text.setString({ "Press Space to continue" });
	_text.setCharacterSize(15);
	auto textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	auto eventManager = _stateMgr->GetContext()->_eventManager;
	eventManager->addCallBack(StateType::Intro, "Intro_Continue", &State_Intro::continueWith, this);
}

void State_Intro::onDestroy()
{
	auto eventManager = _stateMgr->GetContext()->_eventManager;
	eventManager->removeCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::update(const sf::Time& pTime)
{
	if(_timePassed < 5.0f)
	{
		_timePassed += pTime.asSeconds();
		_introSprite.setPosition(_introSprite.getPosition().x, _introSprite.getPosition().y + (48 * pTime.asSeconds()));
	}
}


void State_Intro::draw()
{
	auto window = _stateMgr->GetContext()->_wind->getRenderWindow();

	window->draw(_introSprite);
	if (_timePassed >= 5.0f)
		window->draw(_text);
}

void State_Intro::continueWith(EventDetails* pDetails)
{
	if(_timePassed >= 5.0f)
	{
		_stateMgr->SwitchTo(StateType::MainMenu);
		_stateMgr->Remove(StateType::Intro);
	}
}

void State_Intro::activate()
{
	
}

void State_Intro::deactivate()
{
	
}







