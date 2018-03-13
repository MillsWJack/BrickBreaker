#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
class Brick
{
public:
	Brick(sf::Vector2f position, sf::Vector2f size, bool isHit = false);
	Brick();
	~Brick();

	void Render(sf::RenderWindow& window, std::vector<Brick*> brickList);
	
	void ToggleHit() { m_isHit = true; }

	sf::RectangleShape& GetBrickRect() { return m_brickRect; }
	sf::Vector2f& GetPosition() { return m_position; }
	sf::Vector2f& GetSize() { return m_size; }

private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;

	bool m_isHit;

	sf::RectangleShape m_brickRect;
};



