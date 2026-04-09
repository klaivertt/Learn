#include <iostream>
#include <string>
#include <windows.h>

int main()
{
    std::string userName = "";
    int age = 0;

	do
	{
		std::cout << "Enter you name :" << std::endl;
		std::getline(std::cin, userName);
		std::cout << "Enter your age :" << std::endl;
		std::cin >> age;

	} while (userName.empty() || age <= 0);

	std::cout << "Your name is : " << userName << std::endl;
	std::cout << "Your age is " << age << std::endl;

	if ( age > 18)
	{
		std::cout << "You are an adult your age is " << age << "is over 18" << std::endl;
	}
	else
	{
		std::cout << "You are a child your age is " << age << "is under 18" << std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}