#include "Game.h"

Game::Game() :
	m_window("Brick Breaker", sf::Vector2u(800, 600)),
	m_ball(400, 300, 5, sf::Vector2f(-4.0, 8.0)),
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
	m_elapsed += m_clock.restart();
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

	//Iterate through all bricks in vector to check whether it's
	// colliding with ball
	for (int i = 0; i < m_brickList.size(); i++)
	{
		if (AreColliding(m_ball, m_brickList[i]))
		{
			//If it is, calculate new X and Y direction
			HandleCollisions(m_ball, m_brickList[i]);
			//Toggle the brick to be hit
			m_brickList[i]->ToggleHit();
			//Erase brick from array
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
	//If ball hits Right side
	if ((ball.GetXPosition() + (ball.GetRadius() * 2)) >= 800)
	{
		ball.MultiplyMoveSpeedX(-1);
	}
	//If ball hits left side
	if (ball.GetXPosition() <= 0)
	{
		ball.MultiplyMoveSpeedX(-1);
	}
	//If ball hits bottom
	if (ball.GetYPosition() + (ball.GetRadius() * 2) >= 600)
	{	
		//Once user presses Up key, another ball will spawn
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_ball.Reset();
		}
	}
	//If ball hits top
	if (ball.GetYPosition() <= 0)
	{
		ball.MultiplyMoveSpeedY(-1);
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
	ball.MultiplyMoveSpeedY(-1);
}

void Game::HandleCollisions(Ball& ball, Paddle& paddle)
{
	//Map ball x position (where the minimum x is paddleX, 
	// and the maxiumum x is paddleX + paddle length)
	//to the scale of -360 and +360
	float mappedDegrees = Maths::Map(ball.GetPosition().x, paddle.GetPosition().x, paddle.GetPosition().x + paddle.GetSize().x, -360, 360);
	
	//Convert this mapped value to radians
	float mappedRad = Maths::DegreesToRadians(mappedDegrees);
	
	//Set ball X speed to that radian
	ball.SetMoveSpeedX(mappedRad);

	//Always going to reverse the Y direction
	ball.MultiplyMoveSpeedY(-1);
}