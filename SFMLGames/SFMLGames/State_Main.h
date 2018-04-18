#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_MainMenu : public BaseState {
public:
	State_MainMenu(StateManager* pStateManager);
	~State_MainMenu();

	void onCreate();
	void onDestroy();

	void activate();
	void deactivate();

	void update(const sf::Time& pTime);
	void draw();

	void mouseClick(EventDetails* pDetails);
private:
	sf::Font _font;
	sf::Text _text;

	sf::Vector2f _buttonSize;
	sf::Vector2f _buttonPos;
	unsigned int _buttonPadding;

	sf::RectangleShape _rects[3];
	sf::Text _labels[3];
};