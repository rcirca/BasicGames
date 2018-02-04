#include "TextBox.h"

TextBox::TextBox()
{
	setup(5, 9, 200, sf::Vector2f(0, 0));
}

TextBox::~TextBox()
{
	clear();
}

TextBox::TextBox(int pVisible, int pCharSize, int pWidth, sf::Vector2f pScreenPos)
{
	setup(pVisible, pCharSize, pWidth, pScreenPos);
}

void TextBox::setup(int pVisible, int pCharSize, int pWidth, sf::Vector2f pScreenPos)
{
	_numVisible = pVisible;

	sf::Vector2f offset(2.0f, 2.0f);

	_font.loadFromFile("font/arial.ttf");
	_content.setFont(_font);
	_content.setString("");
	_content.setCharacterSize(pCharSize);
	_content.setFillColor(sf::Color::White);
	_content.setPosition(pScreenPos + offset);

	_backDrop.setSize(sf::Vector2f(pWidth, (pVisible * (pCharSize * 1.2f))));
	_backDrop.setFillColor(sf::Color(90, 90, 90, 90));
	_backDrop.setPosition(pScreenPos);
}

void TextBox::add(std::string pMsg)
{
	_messages.push_back(pMsg);

	if (_messages.size() < 6) 
		return;

	_messages.erase(_messages.begin());
}

void TextBox::draw(sf::RenderWindow& pWindow)
{
	std::string content;

	for (auto& itr : _messages)
		content.append(itr + "\n");

	if(content != "")
	{
		_content.setString(content);
		pWindow.draw(_backDrop);
		pWindow.draw(_content);
	}
}

void TextBox::clear()
{
	_messages.clear();
}






