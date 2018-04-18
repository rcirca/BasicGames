#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Game : public BaseState
{
	State_Game(StateManager* pStateManager);
	~State_Game();

	void onCreate();
	void onDestroy();

	void activate();
	void deactivate();

	void update(const sf::Time& pTime);
	void draw();

	void mainMenu(EventDetails* pDetails);
	void pause(EventDetails* pDetails);

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _increment;
};