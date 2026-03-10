#include "Common.h"
#include "Game.hpp"

#define MAX_HEALTH 100

enum SoldierType
{
	NORMAL,
	HEAVY
};

struct Army
{
	int index = 0;
	int health = 0;
	SoldierType type = SoldierType::NORMAL;
};

int main()
{
	int taille;
	std::cout << "Indique la taille de ton armer : ";
	std::cin >> taille;

	std::vector<std::unique_ptr<Army>> army;

	for (int i = 0; i < taille; i++)
	{
		auto temp = std::make_unique<Army>();
		temp->index = i;
		temp->health = MAX_HEALTH;
		temp->type = (i % 2) == 0 ? SoldierType::HEAVY : SoldierType::NORMAL;

		std::cout << "Index : " << temp->index << std::endl;
		std::cout << "Health : " << temp->health << std::endl;
		std::cout << "type : " << (temp->type == SoldierType::NORMAL ? "Normal" : "Heavy") << std::endl;
		army.push_back(std::move(temp));
	}

	system("pause");

	return EXIT_SUCCESS;
}
