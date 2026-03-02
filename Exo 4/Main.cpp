#include "Common.h"
#include "Game.hpp"

int main()
{
	Game* game = new Game();

	game->Load();

	do
	{
		game->Update();
	} while (!game->GetIsFinished());

	game->DisplayEndGame();

	system("pause");
	delete game;
	return EXIT_SUCCESS;
}