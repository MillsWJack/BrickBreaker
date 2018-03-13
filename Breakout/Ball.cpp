#include "Ball.h"

Ball::Ball(float x, float y, int size, sf::Vector2f moveSpeed):
	m_position(x, y),
	m_size(size),
	m_moveSpeed(moveSpeed)
{
	m_ballCircle.setRadius(size);
}

Ball::~Ball()
{
}

void Ball::Tick()
{
	Move();
}

void Ball::Move()
{
	m_position += m_moveSpeed;
}

void Ball::Render(sf::RenderWindow& window)
{
	m_ballCircle.setFillColor(sf::Color(81,81,81));
	m_ballCircle.setPosition(m_position);
	window.draw(m_ballCircle);
}

void Ball::Reset()
{
	m_position.x = 400;
	m_position.y = 300;
}