#include "Paddle.h"

Paddle::Paddle(float xPos, float yPos, sf::Vector2f size) :
	m_xPos(xPos),
	m_yPos(yPos),
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
		m_xPos -= 0.10;
	}
	else if (direction == Right)
	{
		m_xPos += 0.10;
	}
}

void Paddle::Tick()
{
	CheckCollisions();
}

void Paddle::Reset()
{
	m_xPos = 400;
}

void Paddle::Render(sf::RenderWindow& window)
{
	m_paddleRect.setFillColor(sf::Color(81,81,81));
	m_paddleRect.setPosition(m_xPos, m_yPos);
	window.draw(m_paddleRect);
}

void Paddle::CheckCollisions()
{
	if ((m_xPos + m_size.x) >= 800)
	{
		m_xPos = 800 - m_size.x;
	}
	else if (m_xPos <= 0)
	{
		m_xPos = 0;
	}
}