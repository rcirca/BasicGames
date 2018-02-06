#include "EventManager.h"

EventManager::EventManager() : _hasFocus(true)
{
	loadBindings();
}

EventManager::~EventManager()
{
	for(auto& itr : _bindings)
	{
		delete itr.second;
		itr.second = nullptr;
	}
}


bool EventManager::addBinding(Binding* pBinding)
{
	if (_bindings.find(pBinding->_name) != _bindings.end())
		return false;

	return _bindings.emplace(pBinding->_name, pBinding).second;
}

bool EventManager::removeBindings(std::string pName)
{
	auto itr = _bindings.find(pName);
	if (itr == _bindings.end())
		return false;

	delete itr->second;
	_bindings.erase(itr);
	return true;
}

void EventManager::handleEvent(sf::Event& pEvent)
{
	for(auto& bindingItr : _bindings)
	{
		auto* bind = bindingItr.second;
		for(auto& eventItr : bind->_events)
		{
			auto sfmlEvent = static_cast<EventType>(pEvent.type);
			if (eventItr.first != sfmlEvent)
				continue;

			if(sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if (eventItr.second._code == pEvent.key.code)
				{
					if (bind->_details._keyCode != -1)
						bind->_details._keyCode = eventItr.second._code;

					++(bind->_countOfEvents);
					break;
				}
			} 
			else if( sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp )
			{
				if(eventItr.second._code == pEvent.mouseButton.button)
				{
					bind->_details._mouse.x = pEvent.mouseButton.x;
					bind->_details._mouse.y = pEvent.mouseButton.y;
					if (bind->_details._keyCode != -1)
						bind->_details._keyCode = eventItr.second._code;

					++(bind->_countOfEvents);
					break;
				}
			}
			else
			{
				if (sfmlEvent == EventType::MouseWheel)
					bind->_details._mouseWheelDelta = pEvent.mouseWheel.delta;
				else if (sfmlEvent == EventType::WindowResized)
				{
					bind->_details._size.x = pEvent.size.width;
					bind->_details._size.y = pEvent.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered)
					bind->_details._textEntered = pEvent.text.unicode;
			}
			++(bind->_countOfEvents);
		}
	}
}

void EventManager::loadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("configs/keys.cfg");
	if (!bindings.is_open()) 
	{ 
		std::cout << "Failed to load keys.cfg!" << std::endl; 
		return; 
	}

	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		auto* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			auto start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) { delete bind; bind = nullptr; break; }
			auto type = EventType(stoi(keyval.substr(start, end - start)));
			auto code = stoi(keyval.substr(end + delimiter.length(),
				keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo._code = code;

			bind->BindEvent(type, eventInfo);
		}

		if (!addBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}

void EventManager::setFocus(const bool& pFocus)
{
	_hasFocus = pFocus;
}

void EventManager::update()
{
	if (!_hasFocus)
		return;

	for (auto& bindItr : _bindings) {
		auto* bind = bindItr.second;
		for (auto& eventItr : bind->_events) {
			switch (eventItr.first) {
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eventItr.second._code))) {
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = eventItr.second._code;
					}
					++(bind->_countOfEvents);
				}
				break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eventItr.second._code))) {
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = eventItr.second._code;
					}
					++(bind->_countOfEvents);
				}
				break;
			case(EventType::Joystick):
				// Up for expansion.
				break;
			default: ;
			}
		}

		if (bind->_events.size() == bind->_countOfEvents) {
			auto callItr = _callbacks.find(bind->_name);
			if (callItr != _callbacks.end()) {
				callItr->second(&bind->_details);
			}
		}
		bind->_countOfEvents = 0;
		bind->_details.clear();
	}
}






