#include "Window.h"
#include <SFML/Window/Event.hpp>

Window::Window()
{
	setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string pTitle, const sf::Vector2u& pSize)
{
	setup(pTitle, pSize);
}

Window::~Window()
{
	destroy();
}

void Window::setup(const std::string& pTitle, const sf::Vector2u& pSize)
{
	_windowTitle = pTitle;
	_windowSize = pSize;
	_isDone = false;
	_isFullScreen = false;
	create();
}

void Window::create()
{
	auto style = (_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	_window.create({ _windowSize.x, _windowSize.y, 32 }, _windowTitle, style);
}

void Window::destroy()
{
	_window.close();
}

void Window::update()
{

	sf::Event currentEvent;
	while(_window.pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::Closed)
			_isDone = true;
		else if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::F5)
			toggleFullScreen();

	}
}

void Window::toggleFullScreen()
{
	_isFullScreen = !_isFullScreen;
	destroy();
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