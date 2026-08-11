#include <string>
#include <stdlib.h>

#include <iostream>


#include <vector>
#include <string>

std::string smash(const std::vector<std::string>& _words)
{
	std::string sentences = "";
	for (int i = 0; i < _words.size(); i++)
	{
		if (i != 0)
		{
			sentences += " ";
		}

		sentences += _words[i];
	}
	return sentences;
}
void main(void)
{
	int nb = 0;

	std::cout << "root numb: " << smash({ "hello", "amazing", "world" }) << std::endl;

	system("pause");
}