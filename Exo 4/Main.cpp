#include <string>
#include <stdlib.h>

#include <iostream>

std::string reverseString(const std::string& _str)
{

	std::string tempStr = "";

	for (size_t i = _str.length(); i > 0; i--)
	{
		tempStr += _str[i - 1];
	}
	return tempStr;
}

void main(void)
{
	std::string world = "world";

	std::cout << "reversed world : " << reverseString(world) << std::endl;

	system("pause");
}