#pragma once

#include "Common.h"

class Game
{
public:
	enum Dificulty
	{
		EASY,
		MEDIUM,
		HARD,

		NB_DIFICULTY,
		NONE = -1
	};

	Game();
	~Game();

	void Load(void);
	void Update(void);
	void DisplayEndGame(void);

	// GETER 
	bool GetIsFinished(void);
private:
	int nbToFind = 0;
	int maxRange = 0;
	int minRange = 0;

	int roundLeft = 0;
	int countRound = 0;
	bool isFinished = false;
	bool isFound = false;
	Dificulty dificulty = Dificulty::NONE;
	Dificulty LoadDifficulty(void);
};
