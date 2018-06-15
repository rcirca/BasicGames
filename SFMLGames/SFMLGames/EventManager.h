#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>


enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo
{
	EventInfo() { _code = 0; }
	EventInfo(int pEventCode) { _code = pEventCode; };
	union {
		int _code;
	};
};


struct EventDetails
{
	EventDetails(const std::string& pBindName)
		: _name(pBindName)
	{
		clear();
	}
	std::string _name;
	sf::Vector2i _size;
	sf::Uint32 _textEntered;
	sf::Vector2i _mouse;
	int _mouseWheelDelta;
	int _keyCode;

	void clear()
	{
		_size = sf::Vector2i(0, 0);
		_textEntered = 0;
		_mouse = sf::Vector2i(0, 0);
		_keyCode = -1;
	}
};


using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding
{
	Binding(const std::string& pName)
		: _name(pName), _countOfEvents(0), _details(pName){}

	void BindEvent(EventType pType, EventInfo pInfo = EventInfo())
	{
		_events.emplace_back(pType, pInfo);
	}

	Events _events;
	std::string _name;
	int _countOfEvents;
	EventDetails _details;
};

enum class StateType;

using Bindings = std::unordered_map<std::string, Binding* >;
using CallBackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
using Callbacks = std::unordered_map<StateType, CallBackContainer>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool addBinding(Binding *pBinding);
	bool removeBindings(std::string pName);

	void setCurrentState(StateType pType);
	void setFocus(const bool& pFocus);

	template<class T> // has to be defined in the header
	bool addCallback(StateType pState, const std::string& pName,
		void(T::*pFunc)(EventDetails*), T* pInstance)
	{
		auto itr = _callbacks.emplace(pState, CallBackContainer()).first;
		auto temp = std::bind(pFunc, pInstance, std::placeholders::_1);
		return itr->second.emplace(pName, temp).second;
	}

	bool removeCallback(StateType pState, const std::string& pName)
	{
		auto itr = _callbacks.find(pState);
		if (itr == _callbacks.end())
			return false;
		auto itr2 = itr->second.find(pName);
		if (itr2 == itr->second.end())
			return false;

		itr->second.erase(pName);
		return true;
	}

	void handleEvent(sf::Event& pEvent);
	void update();

	sf::Vector2i getMousePosition(sf::RenderWindow* pRenderWindow = nullptr)
	{
		return (pRenderWindow ? sf::Mouse::getPosition(*pRenderWindow) : sf::Mouse::getPosition());
	}

private:
	void loadBindings();

	StateType _currentStateType;
	Bindings _bindings;
	Callbacks _callbacks;
	bool _hasFocus;
};
