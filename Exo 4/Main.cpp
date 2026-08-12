#include <iostream>

bool isTriangle(int _a, int _b, int _c)
{
    if (_a <= 0 || _b <= 0 || _c <= 0)
    {
        return false;
    }

	int length[3] = { _a, _b, _c };


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (length[i] < length[j])
			{
				std::swap(length[j],length[i]);
			}
		}
	}

	std::cout << length[0] << " + " << length[1] << " = " << length[3] << std::endl;
	if ((length[0] + length[1]) >= length[3])
	{
		return true;
	}
	return false;
}

void main(void)
{

	std::cout << "root numb: " << isTriangle(1,1,2) << std::endl;

	system("pause");
}