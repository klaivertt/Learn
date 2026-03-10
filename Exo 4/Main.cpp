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

    Army *army = new Army[taille];
   
    for (int i = 0; i < taille; i++)
    {
        army[i].index = i;
        army[i].health = MAX_HEALTH;
        army[i].type = (i % 2) == 0 ? SoldierType::HEAVY : SoldierType::NORMAL;

        std::cout << "Index : " << army[i].index << std::endl;
        std::cout << "Health : " << army[i].health << std::endl;
        std::cout << "type : " << (army[i].type == SoldierType::NORMAL ? "Normal" : "Heavy") << std::endl;
    }
        
    delete[] army;

    system("pause");

    return EXIT_SUCCESS;
}
