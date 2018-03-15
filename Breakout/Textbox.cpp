#include "Textbox.h"

Textbox::Textbox()
{
	Setup(255, 9, 200, sf::Vector2f(100, 100));
}

Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	Setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox()
{
}

void Textbox::Setup(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	m_numVisible = visible;
	sf::Vector2f offset(2.0f, 2.0f);

	m_font.loadFromFile("JackPixel.ttf");
	m_content.setFont(m_font);
	m_content.setString("");
	m_content.setCharacterSize(charSize);
	m_content.setFillColor(sf::Color(81,81,81, m_numVisible));
	m_content.setPosition(screenPos + offset);
}

void Textbox::Add(std::string message)
{
	m_message = message;
}

void Textbox::Render(sf::RenderWindow& window)
{
	m_content.setString(m_message);
	window.draw(m_content);
}