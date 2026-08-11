#include <string>
#include <stdlib.h>

#include <iostream>


bool feast(std::string _beast, std::string _dish) {
	return (_beast[0] == _dish[0]) && (_beast[_beast.length() - 1] == _dish[_dish.length() - 1]);
}

void main(void)
{
	int nb = 0;

	std::cout << "root numb: " << feast("great blue heron", "garlic naan") << std::endl;

	system("pause");
}