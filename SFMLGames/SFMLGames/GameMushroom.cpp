#include "GameMushroom.h"

GameMushroom::GameMushroom() : _window("Chapter 4", sf::Vector2u(800, 600)) 
{
	_clock.restart();
	srand(time(nullptr));

	_texture.loadFromFile("images/Mushroom.png");
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	_sprite.setPosition(0, 0);

	_window.getEventManager()->addCallBack(StateType(0), "Move", &GameMushroom::moveSprite, this);
}

GameMushroom::~GameMushroom() {}

void GameMushroom::moveSprite(EventDetails* l_details) 
{
	sf::Vector2i mousepos = _window.getEventManager()->getMousePos(_window.getRenderWindow());
	_sprite.setPosition(mousepos.x, mousepos.y);
	std::cout << "Moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
}

sf::Time GameMushroom::getElapsed() 
{ return _clock.getElapsedTime(); }

void GameMushroom::restartClock() 
{ _clock.restart(); }

Window* GameMushroom::getWindow() 
{ return &_window; }

void GameMushroom::update() 
{
	_window.update();
}

void GameMushroom::render() 
{
	_window.beginDraw();
	// Render here.
	_window.getRenderWindow()->draw(_sprite);
	_window.endDraw();
}