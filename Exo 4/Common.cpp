#include "Common.h"
float RandF(float _min, float _max)
{
	return _min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (_max - _min)));
}

int RandI(int _min, int _max)
{
	return _min + rand() % (_max - _min + 1);
}

int AskPositiveNumberBetween(std::string _message, int _min = 0, int _max = 0)
{
    int tempNumber = 0;
    do
    {
        std::cout << _message << " : ";
        std::cin >> tempNumber;
        std::cout << std::endl;
    } while (tempNumber <= _min || tempNumber >= _max);

    return tempNumber;
}