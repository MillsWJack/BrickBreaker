#include "Brick.h"

Brick::Brick(sf::Vector2f position, sf::Vector2f size, bool isHit):
	m_position(position),
	m_size(size),
	m_isHit(isHit)
{
	m_brickRect.setSize(m_size);
	m_brickRect.setPosition(m_position);
}

Brick::Brick()
{

}

Brick::~Brick()
{
}

void Brick::Render(sf::RenderWindow& window, std::vector<Brick*> brickList)
{
	for (int i = 0; i < brickList.size(); i++)
	{
		if (!brickList[i]->m_isHit)
		{
			brickList[i]->GetBrickRect().setFillColor(sf::Color(81, 81, 81));
			window.draw(brickList[i]->GetBrickRect());
		}
	}
}
