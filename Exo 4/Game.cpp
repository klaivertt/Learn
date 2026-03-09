#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Load(void)
{
	srand(time(NULL));
	dificulty = LoadDifficulty();

	maxRange = 0;
	switch (dificulty)
	{
	case Game::EASY:
		maxRange = 10;
		break;
	case Game::MEDIUM:
		maxRange = 100;
		break;
	case Game::HARD:
		maxRange = 1000;
		break;
	default:
		break;
	}

	nbToFind = RandI(0, maxRange);
	roundLeft = 10;
	countRound = 0;
	std::cout << "You have " << roundLeft << " rounds to find the right number. " << std::endl;
}

void Game::Update(void)
{
	roundLeft--;
	countRound++;

	int tryToFind = AskPositiveNumberBetween("Find the number between " + std::to_string(minRange) + " and " + std::to_string(maxRange),minRange, maxRange);

	if (tryToFind == nbToFind)
	{
		std::cout << "You have found the right number : " << tryToFind << std::endl;
		isFinished = true;
		isFound = true;
	}
	else if (tryToFind > nbToFind)
	{
		std::cout << "Your number is greater than the number to be found" << std::endl;
		std::cout << "Number of attempts remaining : " << roundLeft << std::endl;
	}
	else if (tryToFind < nbToFind)
	{
		std::cout << "Your number is smaller than the number to be found" << std::endl;
		std::cout << "Number of attempts remaining : " << roundLeft << std::endl;
	}

	std::cout << std::endl;

	if (roundLeft <= 0 && !isFound)
	{
		isFinished = true;
		isFound = false;
	}
}

void Game::DisplayEndGame(void)
{
	if (isFound)
	{
		std::cout << "You found the correct number, which was " + std::to_string(nbToFind) + ". Congratulations!" << std::endl;
	}
	else
	{
		std::cout << "You did not manage to find the right number" << std::endl;
		std::cout << "The right number was : " + std::to_string(nbToFind) << std::endl;
	}

	std::cout << "number of attempts :" + std::to_string(countRound) + " , number of rounds remaining : " + std::to_string(roundLeft) << std::endl;

}

bool Game::GetIsFinished(void)
{
	return isFinished;
}

Game::Dificulty Game::LoadDifficulty(void)
{
	int choice = -1;

	do
	{
		std::cout << "Choice Difficulty" << std::endl;
		std::cout << "0 : Easy" << std::endl;
		std::cout << "1 : Medium" << std::endl;
		std::cout << "2 : Hard" << std::endl;
		std::cout << "Ener a number between 0 and 2" << std::endl;
		std::cin >> choice;
	} while (choice > (static_cast<int>(Game::Dificulty::NB_DIFICULTY) - 1) || choice < static_cast<int>(Game::Dificulty::EASY));


	return static_cast<Game::Dificulty>(choice);
}
