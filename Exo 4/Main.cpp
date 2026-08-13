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

    str.erase(str.front(),1);
    str.erase(str.back(),1);
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

void main(void)
{

	std::cout << "root numb: " << XO("zpzpzpp") << std::endl;

	system("pause");
}