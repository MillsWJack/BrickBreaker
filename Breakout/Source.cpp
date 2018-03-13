#include "Game.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	Game game;

	while (!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}