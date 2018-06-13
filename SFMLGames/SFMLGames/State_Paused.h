#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Paused : public BaseState 
{
public:
	State_Paused(StateManager* pStateManager);
	~State_Paused();

	void onCreate();
	void onDestroy();

	void activate();
	void deactivate();

	void update(const sf::Time& pTime);
	void draw();

	void unpause(EventDetails* pDetails);

private:
	sf::Font _font;
	sf::Text _text;
	sf::RectangleShape _rect;
};