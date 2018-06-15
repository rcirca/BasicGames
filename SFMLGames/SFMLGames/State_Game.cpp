#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Game::~State_Game() {}

void State_Game::onCreate() 
{
	_texture.loadFromFile("Mushroom.png");
	_sprite.setTexture(_texture);
	_sprite.setPosition(0, 0);
	_increment = sf::Vector2f(400.0f, 400.0f);

	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->addCallback(StateType::Game, "Key_Escape", &State_Game::mainMenu, this);
	evMgr->addCallback(StateType::Game, "Key_P", &State_Game::pause, this);
}

void State_Game::onDestroy() 
{
	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->removeCallback(StateType::Game, "Key_Escape");
	evMgr->removeCallback(StateType::Game, "Key_P");
}

void State_Game::update(const sf::Time& l_time) 
{
	sf::Vector2u l_windSize = _stateMgr->GetContext()->_wind->getWindowSize();
	sf::Vector2u l_textSize = _texture.getSize();

	if ((_sprite.getPosition().x > l_windSize.x - l_textSize.x && _increment.x > 0) ||
		(_sprite.getPosition().x < 0 && _increment.x < 0))
	{
		_increment.x = -_increment.x;
	}

	if ((_sprite.getPosition().y > l_windSize.y - l_textSize.y && _increment.y > 0) ||
		(_sprite.getPosition().y < 0 && _increment.y < 0))
	{
		_increment.y = -_increment.y;
	}

	_sprite.setPosition(_sprite.getPosition().x + (_increment.x * l_time.asSeconds()),
		_sprite.getPosition().y + (_increment.y * l_time.asSeconds()));
}

void State_Game::draw() 
{
	_stateMgr->GetContext()->_wind->getRenderWindow()->draw(_sprite);
}

void State_Game::mainMenu(EventDetails* l_details) 
{
	_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::pause(EventDetails* l_details) 
{
	_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::activate() {}
void State_Game::deactivate() {}