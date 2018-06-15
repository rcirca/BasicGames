#include "Window.h"
#include <SFML/Window/Event.hpp>

Window::Window()
{
	setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string pTitle, const sf::Vector2u& pSize) : _eventManager("configs/snakeKeys.cfg.txt")
{
	setup(pTitle, pSize);
}

Window::~Window()
{
	_window.close();
}

void Window::setup(const std::string& pTitle, const sf::Vector2u& pSize)
{

	_windowTitle = pTitle;
	_windowSize = pSize;
	_isDone = false;
	_isFullScreen = false;
	_isFocused = true;
	
	_eventManager.addCallback(StateType(0), "Fullscreen_toggle", &Window::toggleFullScreen, this);
	_eventManager.addCallback(StateType(0), "Window_close", &Window::close, this);

	create();
}

void Window::create()
{
	auto style = sf::Style::Default;
	if (_isFullScreen)
		style = sf::Style::Fullscreen;

	_window.create(sf::VideoMode(_windowSize.x, _windowSize.y, 32), _windowTitle, style);
}

void Window::update()
{

	sf::Event currentEvent;
	while(_window.pollEvent(currentEvent))
	{
		if(currentEvent.type == sf::Event::LostFocus)
		{
			_isFocused = false;
			_eventManager.setFocus(false);
		}
		else if(currentEvent.type == sf::Event::GainedFocus)
		{
			_isFocused = true;
			_eventManager.setFocus(true);
		}
		_eventManager.handleEvent(currentEvent);
	}
	_eventManager.update();
}

void Window::toggleFullScreen(EventDetails* pDetails)
{
	_isFullScreen = !_isFullScreen;
	_window.close();
	create();
}

void Window::beginDraw()
{
	_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
	_window.display();
}

bool Window::isDone() const
{
	return _isDone;
}

bool Window::isFullScreen() const
{
	return _isFullScreen;
}

sf::RenderWindow* Window::getRenderWindow()
{
	return &_window;
}


sf::Vector2u Window::getWindowSize() const
{
	return _windowSize;
}


void Window::draw(sf::Drawable& pDrawable)
{
	_window.draw(pDrawable);
}

bool Window::isFocused() const
{
	return _isFocused;
}

EventManager * Window::getEventManager()
{
	return &_eventManager;
}

void Window::close(EventDetails* pDetails)
{
	_isDone = true;
}
