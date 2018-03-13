#include "Game.h"

Game::Game() :
	m_window("Brick Breaker", sf::Vector2u(800, 600)),
	m_ball(400, 300, 5, sf::Vector2f(-0.04, 0.08)),
	m_paddle(sf::Vector2f(400, 550), sf::Vector2f(100, 10))
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
	
	ScreenCollisions(m_ball);
	AreColliding(m_ball, m_paddle);

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

void Game::ScreenCollisions(Ball& ball)
{
	if ((ball.GetXPosition() + (ball.GetRadius() * 2)) >= 800)
	{
		ball.MultiplyMoveSpeedX(-1);
	}
	if (ball.GetXPosition() <= 0)
	{
		ball.MultiplyMoveSpeedX(-1);
	}
	if (ball.GetYPosition() + (ball.GetRadius() * 2) >= 600)
	{
		ball.Reset();
	}
	if (ball.GetYPosition() <= 0)
	{
		ball.MultipleMoveSpeedY(-1);
	}
}

void Game::AreColliding(Ball& ball, Paddle& paddle)
{
	//If ball hits paddle
	if ((ball.GetYPosition() + (ball.GetRadius() * 2)) >= paddle.GetPosition().y &&
		(ball.GetYPosition() + (ball.GetRadius() * 2)) <= (paddle.GetPosition().y + paddle.GetSize().y) &&
		(ball.GetXPosition() + (ball.GetRadius() * 2)) >= paddle.GetPosition().x &&
		(ball.GetXPosition() + (ball.GetRadius() * 2)) <= (paddle.GetPosition().x + paddle.GetSize().x))
	{
		HandleCollisions(ball, paddle);
	}
}

bool Game::AreColliding(Ball& ball, Brick* brick)
{
	//If ball hits a brick
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
	//Reverse Y pos
	ball.MultipleMoveSpeedY(-1);
}

void Game::HandleCollisions(Ball& ball, Paddle& paddle)
{
	float mappedDegrees = Maths::Map(ball.GetPosition().x, paddle.GetPosition().x, paddle.GetPosition().x + paddle.GetSize().x, -10, 10);
	float mappedRad = Maths::DegreesToRadians(mappedDegrees);
	ball.SetMoveSpeedX(mappedRad);
	ball.MultipleMoveSpeedY(-1);
}