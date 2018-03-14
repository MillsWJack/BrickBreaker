#include "window.h"

window::window(const std::string& title, const sf::Vector2u& size):
	m_windowTitle(title),
	m_windowSize(size)
{
	Create();
}

window::~window()
{
}

void window::Create()
{
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle);
	m_window.setFramerateLimit(60);
}

void window::Destroy()
{
	m_window.close();
}

void window::BeginDraw()
{
	m_window.clear(sf::Color::White);
}

void window::EndDraw()
{
	m_window.display();
}

void window::Draw(sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_isDone = true;
		}
	}
}
