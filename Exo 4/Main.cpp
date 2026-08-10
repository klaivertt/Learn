#include <string>
#include <stdlib.h>

#include <iostream>

int string_to_number(const std::string& s)
{
	bool isNeg = false;
	size_t start = 0;

	if (s[0] == '-')
	{
		isNeg = true;
	}
	int n = 0;
	if (isNeg)
	{
		start = 1;
	}
	for (size_t i = start; i < s.length(); i++)
	{
		
		int tempNb = s[i] - '0';
		std::cout << tempNb << std::endl;
		n = n * 10 + tempNb;
	}

	if (isNeg)
	{
		n *= -1;
	}

	return n;
}

void main(void)
{
	std::string nb = "493193";

	std::cout << "root numb: " << string_to_number(nb) << std::endl;

	system("pause");
}