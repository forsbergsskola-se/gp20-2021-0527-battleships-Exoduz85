#include "Game.h"

Game game;

int main()
{
	while (game.running)
	{
		game.start();
	}
	return 0;
}