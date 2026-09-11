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

//unsigned int number(const std::vector<std::pair<int, int>>& busStops) {
//	int passenger = 0;
//	for (int i = 0; i < busStops.size(); i++)
//	{
//		passenger += busStops[i].first - busStops[i].second;
//	}
//
//	return passenger >= 0 ? passenger : 0;
//}
//
//static std::string longest(const std::string& s1, const std::string& s2)
//{
//	std::string str = "";
//	str = s1 + s2;
//	for (int i = 0; i < str.size(); i++)
//	{
//		for (int j = 0; j < str.size(); j++)
//		{
//			if (str[i] == str[j])
//			{
//				str.erase(i);
//			}
//			else if (str[i] < str[j])
//			{
//				std::swap(str[j], str[i]);
//			}
//		}
//	}
//	return str;
//}
//
//std::string sliceString(std::string str)
//{
//	if (str.size() < 2)
//	{
//		return "";
//	}
//
//	str.erase(str.front(), 1);
//	str.erase(str.back(), 1);
//}
//
//bool XO(const std::string& str)
//{
//	int xCount = 0;
//	int oCount = 0;
//
//	for (int i = 0; i < str.size(); i++)
//	{
//		if (str[i] == 'x' || str[i] == 'X')
//		{
//			xCount++;
//		}
//		if (str[i] == 'o' || str[i] == 'O')
//		{
//			oCount++;
//		}
//	}
//
//	if (xCount == oCount)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//#include <regex>
//
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
	int n = 0;

	for (int i = 0; i < roman.size(); i++)
	{
		if ((i + 1 <= roman.size() - 1) && GetValue(roman[i]) < GetValue(roman[i + 1]))
		{
			n -= GetValue(roman[i]);
		}
		else
		{

			n += GetValue(roman[i]);
		}
	}

	return n;
}
//
//bool sp_eng(const std::string& _sentence)
//{
//	std::string word = "english";
//	// to start of string to the end of this string // here to rewrite become the start, and convert to lower case
//	std::transform(_sentence.begin(), _sentence.end(), _sentence.begin(), [](unsigned char c) { return std::tolower(c); });
//
//	return _sentence.find(word) != std::string::npos; 
//}
//
//int basicOp(char _op, int _val1, int _val2)
//{
//	switch (_op)
//	{
//	case '+':
//		return _val1 + _val2;
//	case '-':
//		return _val1 - _val2;
//	case '*':
//		return _val1 * _val2;
//	case '/':
//		return _val2 != 0 ? _val1 / _val2 : 0;
//	}
//}
//
//std::vector<int> move_zeroes(const std::vector<int>& input)
//{
//	// your code here
//		std::vector<int> temp = input;
//		for (int i = 0; i < temp.size(); i++)
//		{
//			if (temp[i] == 0)
//			{
//				temp.erase(temp.begin() + i);
//				temp.push_back(0);
//				i--;
//			}
//		}
//		return temp;
//}
//
//
//#include <string>
//std::string add(const std::string& a, const std::string& b)
//{
//	std::string lower = "";
//	std::string higher = "";
//	if (a.size() > b.size())
//	{
//		lower = b;
//		higher = a;
//	}
//	else
//	{
//		higher = b;
//		lower = a;
//	}
//
//	std::string str = "";
//	int carry = 0;
//	for (int i = lower.size(); i > 0; i--)
//	{
//		int result = (lower[i - 1] - '0') + (higher[(higher.size() - lower.size()) + i - 1] - '0') + carry;
//		if (result > 9)
//		{
//			result %= 10;
//			carry = 1;
//		}
//		else
//		{
//			carry = 0;
//		}
//
//		str.insert(str.begin(), (result + '0'));
//	}
//
//	for (int i = higher.size() - lower.size(); i > 0; i--)
//	{
//		int result = (higher[i - 1] - '0') + carry;
//		if (result > 9)
//		{
//			result %= 10;
//			carry = 1;
//		}
//		else
//		{
//			carry = 0;
//		}
//		str.insert(str.begin(), (result + '0'));
//	}
//
//	if (carry == 1)
//	{
//		str.insert(str.begin(), (carry + '0'));
//	}
//
//	return str;
//}
//long zeros(long n)
//{
//	long numZero = 0;
//	int i = 0;
//	do
//	{
//		numZero += n % int(pow(5, i));
//		i++;
//	} while (pow(5, i) <= n);
//
//	return numZero;
//}
//
//#include <vector>
//
//std::vector<std::vector<int>> create_spiral(int n)
//{
//	if (n < 1)
//	{
//		return {};
//	}
//
//	std::vector<std::vector<int>> grid(n, std::vector<int>(n, 0));
//
//	int minX = 0;
//	int maxX = n - 1;
//	int minY = 0;
//	int maxY = n - 1;
//
//	int x = 0;
//	int y = 0;
//	int v = 1;
//
//	while (minX <= maxX && minY <= maxY)
//	{
//		for (x = minX; x <= maxX; x++)
//		{
//			grid[minY][x] = v++;
//		}
//
//		minY++;
//
//		for (y = minY; y <= maxY; y++)
//		{
//			grid[y][maxX] = v++;
//		}
//
//		maxX--;
//
//		if (minY <= maxY)
//		{
//			for (x = maxX; x >= minX; x--)
//			{
//				grid[maxY][x] = v++;
//			}
//
//			maxY--;
//		}
//
//		if (minX <= maxX)
//		{
//			for (y = maxY; y >= minY; y--)
//			{
//				grid[y][minX] = v++;
//			}
//
//			minX++;
//		}
//	}
//
//	return grid;
//}


#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
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
		switch (walk[i])
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

std::string seriesSum(int n)
{
	// Happy Coding ^_^
	float num = 0.00;
	int div = 1;
	for (size_t i = 0; i < n; i++)
	{
		num += 1.f / div;
		div += 3;
	}
	char buf[20];
	sprintf_s(buf, "%.2f", num);
	return std::string(buf);
}

std::vector<int> digitize(unsigned long n)
{
	std::vector<int> reversedDigit;

	do {
		reversedDigit.push_back(n % 10);
		n /= 10;
	} while (n > 0);

	return reversedDigit;
}

bool betterThanAverage(std::vector<int> classPoints, int yourPoints)
{
	int avr = 0;
	int total = 0;
	for (size_t i = 0; i < classPoints.size(); i++)
	{
		total += classPoints[i];
	}

	avr = total / classPoints.size();

	return avr < yourPoints ? true : false;
}

long long rowSumOddNumbers(unsigned n)
{
	long long total = 0;
	for (unsigned i = 0; i < n; i++)
	{
		total += n * (n + 1) / 2 + i * 2;
	}

	return total;
}


std::vector<std::string> number(const std::vector<std::string>& lines)
{
	std::vector<std::string> str;
	int count = 0;
	for (auto element : lines)
	{
		count++;
		str.push_back(std::to_string(count) + ": " + element);
	}
	return str;
}

std::string removeExclamationMarks(std::string str) {
	//your code here

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '!')
		{
			str.erase(i, 1);
			i--;
		}
	}

	return str;

}

int find_short(std::string str)
{
	int length = 0;

	int min = 0;

	for (auto c : str)
	{
		if (c == ' ')
		{
			if (min == 0 || length < min)
			{
				min = length;
			}

			length = 0;
		}
		else
		{
			length++;
		}
	}
	return min == 0 ? length : min > length ? length : min;
}

std::string countSheep(int number) {
	// your code here

	std::string str = "";

	for (int i = 0; i < number; i++)
	{
		str += std::to_string(i + 1) + " sheep...";
	}

	return str;
}

#include <map>
#include <string>

std::map<char, unsigned> count(const std::string& string)
{
	std::map<char, unsigned> map;

	for (auto c : string)
	{
		if (map.find(c) != map.end())
		{
			map[c] += 1;
		}
		else
		{
			map[c] += 1;
		}
	}

	return map;
}

#include <math.h>

bool isPrime(int num)
{
	// your code here..
	if (num <= 1)
	{
		return false;
	}

	int i = 2;
	while (i <= sqrt(num))
	{
		if (num % i == 0)
		{
			return false;
		}
		i++;
	}

	return true;
}

bool is_square(int n)
{
	// TODO
	if (n < 0)
	{
		return false;
	}

	int d = int(std::round(sqrt(n)));

	return n == (d * d);
}

int rental_car_cost(int d)
{
	int price = d * 40;

	if (7 <= d)
	{
		price -= 20;
	}
	else if (3 <= d)
	{
		price -= 50;
	}

	return price;
}


std::string highestScoringWord(const std::string& str)
{
	int maxScore = 0;
	int currentScore = 0;

	std::string bigestWrd = "";
	std::string currentWrd = "";

	for (auto c : str)
	{
		if (c == ' ')
		{
			if (maxScore < currentScore)
			{
				maxScore = currentScore;
				bigestWrd = currentWrd;
			}
			currentScore = 0;
			currentWrd = "";
		}
		else
		{
			currentWrd += c;
			currentScore += c - 96;
		}
	}

	if (maxScore < currentScore)
	{
		maxScore = currentScore;
		bigestWrd = currentWrd;
	}

	return bigestWrd;
}

class ASum
{
public:
	static long long findNb(long long m)
	{
		long long i = 1;
		long long v = 0;
		while (v < m)
		{
			v += i * i * i;
			if (v == m)
			{
				return i;
			}
			i++;
		}

		return -1;
	}
};


bool isLetter(char _c)
{
	switch (_c)
	{
	case'a':
	case'b':
	case'c':
	case'd':
	case'e':
	case'f':
	case'g':
	case'h':
	case'i':
	case'j':
	case'k':
	case'l':
	case'm':
	case'n':
	case'o':
	case'p':
	case'q':
	case'r':
	case's':
	case't':
	case'u':
	case'v':
	case'x':
	case'w':
	case'y':
	case'z':
		return true;
	default:
		return false;
	}
}

bool isLetter(char c)
{
	return c >= 'a' && c <= 'z';
}

std::string alphabet_position(const std::string& text)
{
	std::string toDigit = "";

	for (size_t i = 0; i < text.size(); i++)
	{
		char c = std::tolower(text[i]);
		if (isLetter(c))
		{
			toDigit += std::to_string(int(c - 96)) + ' ';
		}
	}

	if (!toDigit.empty())
	{
		toDigit.pop_back();
	}

	return toDigit;
}

class LongestConsec
{
public:
	static std::string longestConsec(const std::vector<std::string>& strarr, int k)
	{
		if (strarr.size() == 0 || strarr.size() < k || k <= 0)
		{
			return "";
		}

		std::string longest = "";
		std::string current = "";

		for (size_t i = 0; i < strarr.size(); i++)
		{
			current = "";
			current += strarr[i];
			for (size_t j = 1; j < k; j++)
			{
				if (i + j > strarr.size() - 1)
				{
					break;
				}
				current += strarr[j + i];
			}

			if (longest.size() < current.size())
			{
				longest = current;
			}
		}

		return longest;
	}
};

std::string update_light(std::string _current)
{
	if (_current == "green")
	{
		return "yellow";
	}
	if (_current == "yellow")
	{
		return "red";
	}
	if (_current == "red")
	{
		return "green";
	}
}

#include <vector>

std::vector<int> between(int start, int end)
{
	std::vector<int> res;
	int i = start;
	while (i <= end)
	{
		res.push_back(i);
		i++;
	}

	return res;
}

class Kata
{
public:
	std::vector<int> sortArray(std::vector<int> array)
	{
		std::vector<int> odds;

		for (int value : array)
		{
			if (value % 2 != 0)
			{
				odds.push_back(value);
			}
		}

		std::sort(odds.begin(), odds.end());

		size_t j = 0;

		for (size_t i = 0; i < array.size(); i++)
		{
			if (array[i] % 2 != 0)
			{
				array[i] = odds[j];
				j++;
			}
		}

		return array;
	}
};

std::pair<std::size_t, std::size_t> two_sum(const std::vector<int>& numbers, int target)
{
	for (size_t i = 0; i < numbers.size(); i++)
	{
		for (size_t j = i + 1; j < numbers.size(); j++)
		{
			if (numbers[i] + numbers[j] == target)
			{
				return { i, j };
			}
		}
	}

	return { 0, 0 };
}

std::string reverse_words(std::string str)
{
	std::string reversed = "";

	std::string word = "";
	for (size_t i = 0; i < str.size(); i++)
	{

		if (str[i] == ' ')
		{
			for (int j = word.size() - 1; j >= 0; j--)
			{
				reversed += word[j];
			}
			reversed += str[i];
			word = "";
		}
		else
		{
			word += str[i];
		}
	}

	if (!word.empty())
	{
		for (int i = word.size() - 1; i >= 0; i--)
		{
			reversed += word[i];
		}
	}

	return reversed;
}
#include <cmath>

int cockroach_speed(double s)
{
	return static_cast<int>(std::round(s * (30.0 / 1.08)));
}

std::string sum_str(const std::string& a, const std::string& b)
{
	int n = 0;

	int nA = 0;
	int nB = 0;

	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] != '_')
		{
			nA = nA * 10 + a[i] - '0';
		}
	}
	
	for (size_t i = 0; i < b.size(); i++)
	{
		if (a[i] != '_')
		{
			nB = nB * 10 + b[i] - '0';
		}
	}

	n = (a[0] == '-' ? -nA : nA) + (b[0] == '-' ? -nB : nB);
	
	return std::to_string(n);
}
//
//void main(void)
//{
//
//	//std::cout << "root numb: " << add("99", "1") << std::endl;
//	//create_spiral(1);
//	//std::cout << square_digits(3212);
//
//	//std::vector<std::string> str = towerBuilder(6);
//
//	//for (auto element : str)
//	//{
//	//	std::cout << element << std::endl;
//	//}
//	// 
//	find_short("bitcoin take over the world maybe who knows perhaps");
//	//seriesSum(9);
//
//	system("pause");
//}
//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
///**
// * Auto-generated code below aims at helping you parse
// * the standard input according to the problem statement.
// * ---
// * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
// **/
//
//int main()
//{
//	int light_x; // the X position of the light of power
//	int light_y; // the Y position of the light of power
//	int initial_tx; // Thor's starting X position
//	int initial_ty; // Thor's starting Y position
//	cin >> light_x >> light_y >> initial_tx >> initial_ty; cin.ignore();
//
//	int posX = initial_tx;
//	int posY = initial_ty;
//
//	bool finded = false;
//	// game loop
//	while (!finded)
//	{
//		int remaining_turns; // The remaining amount of turns Thor can move. Do not remove this line.
//		cin >> remaining_turns; cin.ignore();
//
//		int dirX = 0;
//		if (light_x < posX)
//		{
//			if (0 <= posX - 1)
//			{
//				dirX = -1;
//			}
//		}
//
//		if (light_x > posX)
//		{
//			if (posX + 1 < 40)
//			{
//				dirX = 1;
//			}
//		}
//		posX += dirX;
//
//		int dirY = 0;
//		if (light_y < posY)
//		{
//			if (0 <= posY - 1)
//			{
//				dirY = -1;
//			}
//		}
//
//		if (light_y > posY)
//		{
//			if (posY + 1 < 18)
//			{
//				dirY = 1;
//			}
//		}
//		posY += dirY;
//
//		string dir = "";
//
//		if (dirY != 0)
//		{
//			dir += (dirY < 0) ? 'N' : 'S';
//		}
//
//		if (dirX != 0)
//		{
//			dir += (dirX < 0) ? 'W' : 'E';
//		}
//
//		// A single line providing the move to be made: N NE E SE S SW W or NW
//		cout << dir << endl;
//	}
//}

//int main()
//{
//	int w; // width of the building.
//	int h; // height of the building.
//	cin >> w >> h; cin.ignore();
//	int n; // maximum number of turns before game over.
//	cin >> n; cin.ignore();
//	int x0;
//	int y0;
//	cin >> x0 >> y0; cin.ignore();
//
//	// game loop
//	int posX = x0;
//	int posY = y0;
//
//	int xMin = 0;
//	int xMax = w - 1;
//
//	int yMin = 0;
//	int yMax = h - 1;
//
//
//	while (1)
//	{
//		string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
//		cin >> bomb_dir; cin.ignore();
//
//		// Write an action using cout. DON'T FORGET THE "<< endl"
//		// To debug: cerr << "Debug messages..." << endl;
//
//		if (bomb_dir == "U")
//		{
//			yMax = posY - 1;
//		}
//		else if (bomb_dir == "UR")
//		{
//			yMax = posY - 1;
//			xMin = posX + 1;
//		}
//		else if (bomb_dir == "R")
//		{
//			xMin = posX + 1;
//		}
//		else if (bomb_dir == "DR")
//		{
//			yMin = posY + 1;
//			xMin = posX + 1;
//		}
//		else if (bomb_dir == "D")
//		{
//			yMin = posY + 1;
//		}
//		else if (bomb_dir == "DL")
//		{
//			yMin = posY + 1;
//			xMax = posX - 1;
//		}
//		else if (bomb_dir == "L")
//		{
//			xMax = posX - 1;
//		}
//		else if (bomb_dir == "UL")
//		{
//			xMax = posX - 1;
//			yMax = posY - 1;
//		}
//
//		posX = (xMin + xMax) / 2;
//		posY = (yMin + yMax) / 2;
//
//		// the location of the next window Batman should jump to.
//		cout << to_string(posX) + " " + to_string(posY) << endl;
//	}
//}


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <unordered_map>
#include <set>

using namespace std;

/**
 * Connect towns with your train tracks and disrupt the opponent's.
 **/

struct Vec2
{
	int x = 0;
	int y = 0;
	Vec2(int x = 0, int y = 0) : x(x), y(y)
	{}
};

enum Type
{
	PLAINS,
	RIVER,
	MONTAIN,
	POI
};

struct Tiles
{
	int regionId;
	Type type;
	bool inked;
	int tracksOwner = -1;
	int instability = 0;

	Tiles(int _id = 0, Type _t = PLAINS) : regionId(_id), type(_t), inked(false)
	{}
};

struct Town
{
	int id;
	vector<int> desiredConnections;
	Vec2 pos;
	Town(int _id = 0, Vec2 _v = {}, vector<int> _d = {}) : id(_id), pos(_v), desiredConnections(move(_d))
	{}
};


int main()
{
	int my_id; // 0 or 1
	cin >> my_id; cin.ignore();

	Vec2 mSize; // map size
	cin >> mSize.x; cin.ignore();
	cin >> mSize.y; cin.ignore();

	Tiles** map = new Tiles * [mSize.y];

	for (int i = 0; i < mSize.y; i++)
	{
		map[i] = new Tiles[mSize.x];
	}

	for (int i = 0; i < mSize.y; i++)
	{
		for (int j = 0; j < mSize.x; j++)
		{
			int region_id;
			int type; // 0 (PLAINS), 1 (RIVER), 2 (MOUNTAIN), 3 (POI)
			cin >> region_id >> type; cin.ignore();

			map[i][j] = Tiles(region_id, Type(type));

		}
	}

	int town_count;
	vector<Town> towns;

	cin >> town_count; cin.ignore();
	for (int i = 0; i < town_count; i++)
	{
		int town_id;
		int town_x;
		int town_y;
		string desired_connections; // comma-separated town ids e.g. 0,1,2,3
		cin >> town_id >> town_x >> town_y >> desired_connections; cin.ignore();

		vector<int> desired;

		stringstream ss(desired_connections);
		string token;
		while (getline(ss, token, ','))
		{
			desired.push_back(stoi(token));
		}

		towns.push_back(Town(town_id, Vec2(town_x, town_y), desired));
	}

	unordered_map<int, Town*> townById;
	for (auto& town : towns)
	{
		townById[town.id] = &town;
	}

	set<int> townRegions;
	for (auto& t : towns) {
		townRegions.insert(map[t.pos.y][t.pos.x].regionId);
	}

	int foe_id = 1 - my_id;
	int disruptTarget = -1; // -1 = pas de cible en cours


	// game loop
	while (true)
	{
		int my_score;
		cin >> my_score; cin.ignore();
		int foe_score;
		cin >> foe_score; cin.ignore();
		for (int i = 0; i < mSize.y; i++) {
			for (int j = 0; j < mSize.x; j++) {
				int tracks_owner;
				int instability; // region inked (destroyed) when this >= 3.
				bool inked; // true if region is destroyed.
				string part_of_active_connections; // if this cell is part of one or more railway connections, this will be town ids (separated by -) in a list separated by commas. e.g. 0-1,1-2,1-3. "x" otherwise.
				cin >> tracks_owner >> instability >> inked >> part_of_active_connections; cin.ignore();

				Tiles& tile = map[i][j];

				if (disruptTarget != -1 && tile.regionId == disruptTarget && tile.inked)
				{
					disruptTarget = -1;
				}

				if (disruptTarget == -1 && tile.tracksOwner == foe_id && !tile.inked
					&& townRegions.find(tile.regionId) == townRegions.end())
				{
					disruptTarget = tile.regionId;
				}

				tile.inked = inked;
				tile.instability = instability;
				tile.tracksOwner = tracks_owner;

			}
		}

		int minDist = -1;
		Town A, B;
		for (int i = 0; i < towns.size(); i++)
		{
			for (int j = 0; j < towns.size(); j++)
			{
				if (i != j)
				{
					Vec2 townA = towns[i].pos;
					Vec2 townB = towns[j].pos;

					int dist = abs(townB.x - townA.x) + abs(townB.y - townA.y);
					if (minDist == -1 || dist < minDist)
					{
						minDist = dist;
						A = towns[i];
						B = towns[j];
					}
				}
			}
		}

		string actions = "";

		if (disruptTarget != -1) {
			actions += "DISRUPT " + to_string(disruptTarget) + ";";
		}

		for (auto& t : towns) {
			for (int destId : t.desiredConnections) {
				Town* dest = townById[destId];
				actions += "AUTOPLACE " + to_string(t.pos.x) + " " + to_string(t.pos.y)
					+ " " + to_string(dest->pos.x) + " " + to_string(dest->pos.y) + ";";
			}
		}

		if (actions.empty()) {
			actions = "WAIT";
		}

		cout << actions << endl;

		if (actions.empty()) {
			actions = "WAIT";
		}
		cout << actions << endl;
	}


	// delete part
	for (int i = 0; i < mSize.y; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}