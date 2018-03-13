#pragma once
#include <SFML\Graphics.hpp>

enum Direction { Left = 0, Right = 1 };

class Paddle
{
public:
	Paddle(sf::Vector2f, sf::Vector2f size);
	Paddle();
	~Paddle();

	void Move(Direction direction);
	void Tick();
	void Reset();
	void Render(sf::RenderWindow& window);

	sf::Vector2f& GetPosition() { return m_position; };
	sf::Vector2f& GetSize() { return m_size; }
	sf::RectangleShape& GetPaddle() { return m_paddleRect; }

private:
	void CheckCollisions();
	
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::RectangleShape m_paddleRect;
};

