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

#include <regex>

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

std::vector<int> move_zeroes(const std::vector<int>& input)
{
	// your code here
		std::vector<int> temp = input;
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] == 0)
			{
				temp.erase(temp.begin() + i);
				temp.push_back(0);
				i--;
			}
		}
		return temp;
}


#include <string>
std::string add(const std::string& a, const std::string& b)
{
	std::string lower = "";
	std::string higher = "";
	if (a.size() > b.size())
	{
		lower = b;
		higher = a;
	}
	else
	{
		higher = b;
		lower = a;
	}

	std::string str = "";
	int carry = 0;
	for (int i = lower.size(); i > 0; i--)
	{
		int result = (lower[i - 1] - '0') + (higher[(higher.size() - lower.size()) + i - 1] - '0') + carry;
		if (result > 9)
		{
			result %= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}

		str.insert(str.begin(), (result + '0'));
	}

	for (int i = higher.size() - lower.size(); i > 0; i--)
	{
		int result = (higher[i - 1] - '0') + carry;
		if (result > 9)
		{
			result %= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		str.insert(str.begin(), (result + '0'));
	}

	if (carry == 1)
	{
		str.insert(str.begin(), (carry + '0'));
	}

	return str;
}
long zeros(long n)
{
	long numZero = 0;
	int i = 0;
	do
	{
		numZero += n % int(pow(5, i));
		i++;
	} while (pow(5, i) <= n);

	return numZero;
}

#include <vector>

std::vector<std::vector<int>> create_spiral(int n)
{
	if (n < 1)
	{
		return {};
	}

	std::vector<std::vector<int>> grid(n, std::vector<int>(n, 0));

	int minX = 0;
	int maxX = n - 1;
	int minY = 0;
	int maxY = n - 1;

	int x = 0;
	int y = 0;
	int v = 1;

	while (minX <= maxX && minY <= maxY)
	{
		for (x = minX; x <= maxX; x++)
		{
			grid[minY][x] = v++;
		}

		minY++;

		for (y = minY; y <= maxY; y++)
		{
			grid[y][maxX] = v++;
		}

		maxX--;

		if (minY <= maxY)
		{
			for (x = maxX; x >= minX; x--)
			{
				grid[maxY][x] = v++;
			}

			maxY--;
		}

		if (minX <= maxX)
		{
			for (y = maxY; y >= minY; y--)
			{
				grid[y][minX] = v++;
			}

			minX++;
		}
	}

	return grid;
}


#include <iostream>
#include <algorithm>
#include <vector>
uint64_t descendingOrder(uint64_t a)
{
	uint64_t sorted = 0;
	std::vector<int> digit;
	while (a != 0)
	{
		digit.push_back(a % 10);
		a /= 10;
	}
	std::sort(digit.begin(), digit.end(), std::greater<int>());

	for (size_t i = 0; i < digit.size(); i++)
	{
		sorted = sorted * 10 + digit[i];
	}
	return sorted;
}
#include <cmath>
int square_digits(int num)
{
	std::string str = std::to_string(num);

	std::string v = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		int n = str[i] - '0';
		v += std::to_string(n * n);
	}

	return std::stoi(v);
}

std::string get_middle(std::string input)
{
	std::string str = "";
	if (input.size() % 2 == 0)
	{
		str += input[input.size() / 2 - 1];
		str += input[input.size() / 2];
	}
	else
	{
		str += input[input.size() / 2];
	}

	return str;
}

std::vector<std::string> towerBuilder(unsigned nFloors) {
	std::vector<std::string> str;

	for (size_t i = 0; i < nFloors; i++)
	{
		std::string floor = "";

		for (size_t j = 1; j < nFloors * 2; j++)
		{
			if ((nFloors - i) <= j && j <= (nFloors + i))
			{
				floor += '*';
			}
			else
			{
				floor += ' ';
			}
		}

		str.push_back(floor);
	}

	return str;
}

int maxSequence(const std::vector<int>& arr)
{
	if (arr.size() < 1)
	{
		return 0;
	}

	int currentSum = arr[0];
	int max = arr[0];
	for (size_t i = 1; i < arr.size(); i++)
	{
		int x = arr[i];

		if (currentSum < 0)
		{
			currentSum = x;
		}
		else
		{
			currentSum += x;
		}

		if (max < currentSum)
		{
			max = currentSum;
		}
	}
	
	return max < 0 ? 0 : max;
}

#include <array>

int points(const std::array<std::string, 10>& games)
{
	int point = 0;
	
	for (size_t i = 0; i < games.size(); i++)
	{
		std::string score = games[i];
		
		if (score[0] > score[2])
		{
			point += 3;
		}
		else if (score[0] == score[2])
		{
			point += 1;
		}



	}

	return point;
}

bool isValidWalk(std::vector<char> walk)
{
	if (walk.size() < 10 || 10 < walk.size())
	{
		return false;
	}

	int position = 0;

	for (size_t i = 0; i < walk.size(); i++)
	{
		switch(walk[i])
		{
			case 'n':
				position += 1;
				break;
			case 's': 
				position -= 1;
				break;
			case'w': 
				position -= 100;
				break;
			case 'e':
				position += 100;
				break;
		}
	}

	return position == 0 ? true : false;
}

void main(void)
{

	//std::cout << "root numb: " << add("99", "1") << std::endl;
	//create_spiral(1);
	//std::cout << square_digits(3212);

	std::vector<std::string> str = towerBuilder(6);

	for (auto element : str)
	{
		std::cout << element << std::endl;
	}


	system("pause");
}