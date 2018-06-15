#include "State_Main.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* pStateManager) : BaseState(pStateManager)
{
	
}

State_MainMenu::~State_MainMenu()
{
	
}

void State_MainMenu::onCreate()
{
	_font.loadFromFile("arial.ttf");
	_text.setFont(_font);
	_text.setString(sf::String("Main Menu:"));
	_text.setCharacterSize(18);

	auto textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	_text.setPosition(400, 100);

	_buttonSize = sf::Vector2f(300.0f, 32.0f);
	_buttonPos = sf::Vector2f(400, 200);
	_buttonPadding = 4;

	std::string str[3];
	str[0] = "Play";
	str[1] = "Credits";
	str[2] = "Exit";

	for(auto i = 0; i < 3; ++i)
	{
		sf::Vector2f buttonPosition(_buttonPos.x, _buttonPos.y + (i * (_buttonSize.y + _buttonPadding)));

		_rects[i].setSize(_buttonSize);
		_rects[i].setFillColor(sf::Color::Red);

		_rects[i].setOrigin(_buttonSize.x / 2.0f, _buttonSize.y / 2.0f);
		_rects[i].setPosition(buttonPosition);

		_labels[i].setFont(_font);
		_labels[i].setString(sf::String(str[i]));
		_labels[i].setCharacterSize(12);

		auto rect = _labels[i].getLocalBounds();
		_labels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

		_labels[i].setPosition(buttonPosition);
	}

	auto eventManager = _stateMgr->GetContext()->_eventManager;
	eventManager->addCallback(StateType::MainMenu, "Mouse_Left", &State_MainMenu::mouseClick, this);;
}

void State_MainMenu::onDestroy()
{
	auto eventManager = _stateMgr->GetContext()->_eventManager;
	eventManager->removeCallback(StateType::MainMenu, "Mouse_Left");
}

void State_MainMenu::activate()
{
	if(_stateMgr->HasState(StateType::Game) && _labels[0].getString() == "Play")
	{
		_labels[0].setString(sf::String("Resume"));
		auto rect = _labels[0].getLocalBounds();
		_labels[0].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	}
}

void State_MainMenu::draw()
{
	auto window = _stateMgr->GetContext()->_wind->getRenderWindow();
	window->draw(_text);
	for(auto i = 0; i < 3; ++i)
	{
		window->draw(_rects[i]);
		window->draw(_labels[i]);
	}
}

void State_MainMenu::mouseClick(EventDetails* pDetails)
{
	auto mousePos = pDetails->_mouse;

	auto halfX = _buttonSize.x / 2.0f;
	auto halfY = _buttonSize.y / 2.0f;

	for(auto i = 0; i < 3; ++i)
	{
		if(mousePos.x >= _rects[i].getPosition().x - halfX
			&& mousePos.x <= _rects[i].getPosition().x + halfX
			&& mousePos.y >= _rects[i].getPosition().y - halfY
			&& mousePos.y <= _rects[i].getPosition().y + halfY)
		{
			if (i == 0)
				_stateMgr->SwitchTo(StateType::Game);
			else if (i == 1) {}
			else if (i == 2)
				_stateMgr->GetContext()->_wind->close();
		}
	}
}




void State_MainMenu::update(const sf::Time& pTime)
{
	
}

void State_MainMenu::deactivate()
{
	
}

