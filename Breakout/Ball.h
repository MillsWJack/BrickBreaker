#pragma once
#include <SFML\Graphics.hpp>

class Ball
{
public:
	Ball(float x, float y, int size, sf::Vector2f moveSpeed);
	~Ball();

	void Tick();
	void Move();
	void Render(sf::RenderWindow& window);
	void Reset();

	void SetMoveSpeedX(float setter) { m_moveSpeed.x *= setter; }
	void SetMoveSpeedY(float setter) { m_moveSpeed.y *= setter; }
	
	sf::Vector2f GetMoveSpeed() { return m_moveSpeed; }
	sf::Vector2f GetPosition() { return m_position; }
	sf::CircleShape& GetBall() { return m_ballCircle; }

	float GetRadius() { return m_ballCircle.getRadius(); }
	float GetYPosition() { return m_position.y; }
	float GetXPosition() { return m_position.x; }

private:
	int m_size;
	sf::Vector2f m_moveSpeed;
	sf::Vector2f m_position;
	sf::CircleShape m_ballCircle;
};

