#include <iostream>

std::string DNAtoRNA(std::string dna) {
	for (int i = 0; i < dna.length(); i++)
	{
		if (dna[i] == 'T')
		{
			dna[i] = 'U';
		}
	}

	return dna;
}

#include <utility>
#include <vector>

unsigned int number(const std::vector<std::pair<int, int>>& busStops) {
	int passenger = 0;
	for (int i = 0; i < busStops.size(); i++)
	{
		passenger += busStops[i].first - busStops[i].second;
	}

	return passenger >= 0 ? passenger : 0;
}

static std::string longest(const std::string& s1, const std::string& s2)
{
	std::string str = "";
	str = s1 + s2;
	for (int i = 0; i < str.size(); i++)
	{
		for (int j = 0; j < str.size(); j++)
		{
			if (str[i] == str[j])
			{
				str.erase(i);
			}
			else if (str[i] < str[j])
			{
				std::swap(str[j], str[i]);
			}
		}
	}
	return str;
}

std::string sliceString(std::string str)
{
	if (str.size() < 2)
	{
		return "";
	}

	str.erase(str.front(), 1);
	str.erase(str.back(), 1);
}

bool XO(const std::string& str)
{
	int xCount = 0;
	int oCount = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == 'x' || str[i] == 'X')
		{
			xCount++;
		}
		if (str[i] == 'o' || str[i] == 'O')
		{
			oCount++;
		}
	}

	if (xCount == oCount)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int GetValue(char& _c)
{
	switch (_c)
	{
	case 'I':
		return 1;
	case 'V':
		return 5;
	case 'X':
		return 10;
	case 'L':
		return 50;
	case 'C':
		return 100;
	case 'D':
		return 500;
	case 'M':
		return 1000;
	}
}


int solution(std::string roman)
{
	int count = 0;

	for (int i = 0; i < roman.size(); i++)
	{
		if (GetValue(roman[i]) >= GetValue(roman[i + 1]))
		{
			count += GetValue(roman[i]);
		}
		else
		{
			count -= GetValue(roman[i]);
		}
	}

	return count;
}

#include <algorithm>
bool sp_eng(const std::string& _sentence)
{
	std::string word = "english";
	// to start of string to the end of this string // here to rewrite become the start, and convert to lower case
	std::transform(_sentence.begin(), _sentence.end(), _sentence.begin(), [](unsigned char c) { return std::tolower(c); });

	return _sentence.find(word) != std::string::npos; 
}

int basicOp(char _op, int _val1, int _val2)
{
	switch (_op)
	{
	case '+':
		return _val1 + _val2;
	case '-':
		return _val1 - _val2;
	case '*':
		return _val1 * _val2;
	case '/':
		return _val2 != 0 ? _val1 / _val2 : 0;
	}
}

void main(void)
{

	std::cout << "root numb: " << solution("IV") << std::endl;

	system("pause");
}