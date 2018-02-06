#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"

namespace sf {
	class Drawable;
}

class Window
{
public:
	Window();
	Window(const std::string pTitle, const sf::Vector2u& pSize);
	~Window();

	void beginDraw();
	void endDraw();

	void update();

	bool isDone() const;
	bool isFullScreen() const;
	sf::RenderWindow* getRenderWindow();
	sf::Vector2u getWindowSize() const;

	void toggleFullScreen(EventDetails* pDetails);

	void draw(sf::Drawable& pDrawable);

	bool isFocused();
	EventManager* getEventManager();
	void close(EventDetails* pDetails = nullptr);

private:
	void setup(const std::string& pTitle, const sf::Vector2u& pSize);
	void destroy();
	void create();

	EventManager _eventManager;
	bool _isFocused;
	sf::RenderWindow _window;
	sf::Vector2u _windowSize;
	std::string _windowTitle;
	bool _isDone;
	bool _isFullScreen;

};
