#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState 
{
public:
	State_Intro(StateManager* pStateManager);
	~State_Intro();

	void onCreate();
	void onDestroy();

	void activate();
	void deactivate();

	void update();
	void draw();

	void continueWith(EventDetails* pDetails);

private:
	sf::Texture _introTexture;
	sf::Sprite _introSprite;
	sf::Font _font;
	sf::Text _text;

	float _timePassed;
};