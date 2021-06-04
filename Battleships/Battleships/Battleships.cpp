#include "Game.h"

Game game;

int main()
{
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	srand(ms);
	while (game.running)
	{
		game.start();
	}
	return 0;
}