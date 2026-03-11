#include "GameData.h"

GameData* GameData::instance = nullptr;

GameData* GameData::GetInstance(void)
{
	if (instance == nullptr)
	{
		instance = new GameData();
		//printf("New Singleton\n");
	}
	return instance;
}
