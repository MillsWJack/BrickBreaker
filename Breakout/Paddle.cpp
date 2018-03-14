#include "Paddle.h"

Paddle::Paddle(sf::Vector2f position, sf::Vector2f size) :
	m_position(position),
	m_size(size)
{
	m_paddleRect.setSize(m_size);
}

Paddle::Paddle()
{

}

Paddle::~Paddle()
{
}

void Paddle::Move(Direction direction)
{
	if (direction == Left)
	{
		m_position.x -= 10;
	}
	else if (direction == Right)
	{
		m_position.x += 10;
	}
}

void Paddle::Tick()
{
	CheckCollisions();
}

void Paddle::Reset()
{
	m_position.x = 400;
}

void Paddle::Render(sf::RenderWindow& window)
{
	m_paddleRect.setFillColor(sf::Color(81,81,81));
	m_paddleRect.setPosition(m_position.x, m_position.y);
	window.draw(m_paddleRect);
}

void Paddle::CheckCollisions()
{
	if ((m_position.x + m_size.x) >= 800)
	{
		m_position.x = 800 - m_size.x;
	}
	else if (m_position.x <= 0)
	{
		m_position.x = 0;
	}
}