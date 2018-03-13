#include "Game.h"

Game::Game() :
	m_window("Brick Breaker", sf::Vector2u(800, 600)),
	m_ball(400, 300, 5, sf::Vector2f(-0.04, 0.08)),
	m_paddle(400, 550, sf::Vector2f(100, 10))
{
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			Brick* brick = new Brick(sf::Vector2f(col * 100, row * 25), sf::Vector2f(100, 25));
			m_brickList.push_back(brick);
		}
	}
}

Game::~Game()
{
}

void Game::RestartClock()
{
	m_elapsed += m_clock.restart().asSeconds();
}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_paddle.Move(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_paddle.Move(Direction::Right);
	}
}

void Game::Update()
{
	m_window.Update();
	m_ball.Tick();
	m_paddle.Tick();
	if (AreColliding(m_ball, m_paddle))
	{
		HandleCollisions(m_ball, m_paddle);
	}
	for (int i = 0; i < m_brickList.size(); i++)
	{
		if (AreColliding(m_ball, m_brickList[i]))
		{
			HandleCollisions(m_ball, m_brickList[i]);
			m_brickList[i]->ToggleHit();
			m_brickList.erase(m_brickList.begin() + i);
		}
	}
}

void Game::Render()
{
	m_window.BeginDraw();
	m_paddle.Render(*m_window.GetRenderWindow());
	m_ball.Render(*m_window.GetRenderWindow());
	m_brick.Render(*m_window.GetRenderWindow(), m_brickList);
	m_window.EndDraw();
}

bool Game::AreColliding(Ball& ball, Paddle& paddle)
{
	//If ball hits paddle
	if ((ball.GetYPosition() + (ball.GetRadius() * 2)) >= paddle.GetYPos() &&
		(ball.GetYPosition() + (ball.GetRadius() * 2)) <= (paddle.GetYPos() + paddle.GetHeight()) &&
		(ball.GetXPosition() + (ball.GetRadius() * 2)) >= paddle.GetXPos() &&
		(ball.GetXPosition() + (ball.GetRadius() * 2)) <= (paddle.GetXPos() + paddle.GetLength()))
	{
		return true;
	}
	if ((ball.GetXPosition() + (ball.GetRadius() * 2)) >= 800)
	{
		ball.SetMoveSpeedX(-1);
	}
	if (ball.GetXPosition() <= 0)
	{
		ball.SetMoveSpeedX(-1);
	}
	if (ball.GetYPosition() + (ball.GetRadius() * 2) >= 600)
	{
		ball.Reset();
	}
	if (ball.GetYPosition() <= 0)
	{
		ball.SetMoveSpeedY(-1);
	}

	return false;
}

bool Game::AreColliding(Ball& ball, Brick* brick)
{
	if (ball.GetPosition().y >= brick->GetPosition().y &&
		ball.GetPosition().y <= brick->GetPosition().y + brick->GetSize().y &&
		ball.GetPosition().x >= brick->GetPosition().x &&
		ball.GetPosition().x <= brick->GetPosition().x + brick->GetSize().x)
	{
		return true;
	}

	return false;
}

void Game::HandleCollisions(Ball& ball, Brick* brick)
{
	//Ball is coming from the left and hits left side of brick
	if(ball.GetMoveSpeed().x > 0 &&
		ball.GetPosition().x >= brick->GetPosition().x &&
		ball.GetPosition().x <= brick->GetPosition().x + (brick->GetSize().x / 2))
	{
		ball.SetMoveSpeedX(-1);
		ball.SetMoveSpeedY(-1);
	}

	//Ball is coming from the left and hits the right side of the paddle
	else if (ball.GetMoveSpeed().x > 0 &&
		ball.GetPosition().x >= brick->GetPosition().x + (brick->GetSize().x / 2) &&
		ball.GetPosition().x <= brick->GetPosition().x + brick->GetSize().x)
	{
		ball.SetMoveSpeedX(1);
		ball.SetMoveSpeedY(-1);
	}

	//Ball is coming from the right and hits the right side of the paddle
	else if (ball.GetMoveSpeed().x < 0 &&
		ball.GetPosition().x >= brick->GetPosition().x + (brick->GetSize().x / 2) &&
		ball.GetPosition().x <= brick->GetPosition().x + brick->GetSize().x)
	{
		ball.SetMoveSpeedX(-1);
		ball.SetMoveSpeedY(-1);
	}

	//Ball is coming from the right and hits the left side of the paddle
	else if (ball.GetMoveSpeed().x < 0 &&
		ball.GetPosition().x >= brick->GetPosition().x &&
		ball.GetPosition().x <= brick->GetPosition().x + (brick->GetSize().x / 2))
	{
		ball.SetMoveSpeedX(1);
		ball.SetMoveSpeedY(-1);
	}
}

void Game::HandleCollisions(Ball& ball, Paddle& paddle)
{
	//Ball is coming from the left and hits the left side of the paddle
	if (ball.GetMoveSpeed().x > 0 &&
		ball.GetPosition().x >= paddle.GetXPos() &&
		ball.GetPosition().x <= paddle.GetXPos() + (paddle.GetLength() / 2))
	{
		ball.SetMoveSpeedX(-1);
		ball.SetMoveSpeedY(-1);
	}

	//Ball is coming from the left and hits the right side of the paddle
	else if (ball.GetMoveSpeed().x > 0 &&
		ball.GetPosition().x >= paddle.GetXPos() + (paddle.GetLength() / 2) &&
		ball.GetPosition().x <= paddle.GetXPos() + paddle.GetLength())
	{
		ball.SetMoveSpeedX(1);
		ball.SetMoveSpeedY(-1);
	}

	//Ball is coming from the right and hits the right side of the paddle
	else if (ball.GetMoveSpeed().x < 0 &&
		ball.GetPosition().x >= paddle.GetXPos() + (paddle.GetLength() / 2) &&
		ball.GetPosition().x <= paddle.GetXPos() + paddle.GetLength())
	{
		ball.SetMoveSpeedX(-1);
		ball.SetMoveSpeedY(-1);
	}

	//Ball is coming from the right and hits the left side of the paddle
	else if (ball.GetMoveSpeed().x < 0 &&
		ball.GetPosition().x >= paddle.GetXPos() &&
		ball.GetPosition().x <= paddle.GetXPos() + (paddle.GetLength() / 2))
	{
		ball.SetMoveSpeedX(1);
		ball.SetMoveSpeedY(-1);
	}
}