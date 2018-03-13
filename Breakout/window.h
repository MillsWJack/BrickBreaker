#pragma once
#include <SFML\Graphics.hpp>
class window
{
public:
	window(const std::string& title, const sf::Vector2u& size);
	~window();

	void Create();
	void Destroy();

	sf::RenderWindow* GetRenderWindow() { return &m_window; }

	void BeginDraw();
	void EndDraw();
	void Draw(sf::Drawable& drawable);
	void Update();

	inline bool IsDone() { return m_isDone; }

private:

	sf::RenderWindow m_window;
	std::string m_windowTitle;
	sf::Vector2u m_windowSize;

	bool m_isDone;
};

