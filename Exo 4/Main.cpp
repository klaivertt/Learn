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

void main(void)
{

	std::cout << "root numb: " << DNAtoRNA("GCAT") << std::endl;

	system("pause");
}