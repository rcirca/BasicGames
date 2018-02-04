#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


namespace sf {
	class RenderWindow;
}

using MessageContainer = std::vector<std::string>;

class TextBox
{
public:
	TextBox();
	TextBox(int pVisible, int pCharSize, int pWidth, sf::Vector2f pScreenPos);
	~TextBox();

	void setup(int pVisible, int pCharSize, int pWidth, sf::Vector2f pScreenPos);
	void add(std::string pMsg);
	void clear();
	void TextBox::draw(sf::RenderWindow& pWindow);

private:
	sf::RectangleShape _backDrop;
	sf::Font _font;
	sf::Text _content;
	MessageContainer _messages;
	int _numVisible;
};
