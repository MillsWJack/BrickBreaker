#pragma once
#include <SFML\Graphics.hpp>
class Textbox
{
public:
	Textbox();
	Textbox(int visible, int charSize, int width, sf::Vector2f screenPos);
	~Textbox();

	void Setup(int visible, int charSize, int width, sf::Vector2f screenPos);
	void Add(std::string message);
	void Clear() { m_message = ""; }

	void Render(sf::RenderWindow& wind);

private:
	std::string m_message;
	int m_numVisible;

	sf::Font m_font;
	sf::Text m_content;

};

