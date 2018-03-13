#pragma once
#include <SFML\Graphics.hpp>

enum Direction { Left = 0, Right = 1 };

class Paddle
{
public:
	Paddle(float xPos, float yPos, sf::Vector2f size);
	Paddle();
	~Paddle();

	void Move(Direction direction);
	void Tick();
	void Reset();
	void Render(sf::RenderWindow& window);

	float GetXPos() { return m_xPos; }
	float GetYPos() { return m_yPos; }
	float GetLength() { return m_paddleRect.getSize().x; }
	float GetHeight() { return m_paddleRect.getSize().y; }
	sf::RectangleShape& GetPaddle() { return m_paddleRect; }

private:
	void CheckCollisions();
	
	float m_yPos;
	float m_xPos;
	sf::Vector2f m_size;
	sf::RectangleShape m_paddleRect;
};

