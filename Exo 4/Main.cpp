#include <string>
#include <stdlib.h>

#include <iostream>


std::string number_to_string(int _num)
{
	std::string str = "";

	if (_num == 0)
	{
		return "0";
	}

	if (_num < 0)
	{
		str += '-';
	}
	int num = std::abs(_num);
	std::string temp = "";
	while (num != 0)
	{
		int n = num % 10;
		num /= 10;
		temp += n + '0';
	}

	for (int i = temp.length(); i > 0 ; --i)
	{
		str += temp[i - 1];
	}

	return str;
}

void main(void)
{
	int nb = 0;

	std::cout << "root numb: " << number_to_string(nb) << std::endl;

	system("pause");
}