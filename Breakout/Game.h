#pragma once
#include "window.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Maths.h"
#include "Textbox.h"

#include <vector>

class Game
{
public:
	Game();
	~Game();

	window* GetWindow() { return &m_window; }

	sf::Time GetElapsed() { return m_clock.getElapsedTime(); }
	void RestartClock();

	void HandleInput();
	void Update();
	void Render();

private:
	void ScreenCollisions(Ball& ball);
	void AreColliding(Ball& ball, Paddle& paddle);
	bool AreColliding(Ball& ball, Brick* brick);
	void HandleCollisions(Ball& ball, Brick* brick);	
	void HandleCollisions(Ball& ball, Paddle& paddle);

	sf::Clock m_clock;
	sf::Time m_elapsed;

	std::vector<Brick*> m_brickList;
	int m_brickAmount;

	window m_window;
	Ball m_ball;
	Paddle m_paddle;
	Brick m_brick;
	Textbox m_scoreTextBox;
	Textbox m_instructTextBox;
};

