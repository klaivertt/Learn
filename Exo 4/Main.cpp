#include "Common.h"
#include "Game.hpp"

class PasswodManager
{
private:
	int attempt = 5;
	bool correctPassword = false;
	std::string inputPassword = "";
	std::string password = "Pasword123456789";

public:
	PasswodManager()
	{
		do
		{
			std::cout << "saisir le mots de passe";
			std::getline(std::cin, inputPassword);

			if (inputPassword == password)
			{
				std::cout << "Mots de passe correcte" << std::endl;
				correctPassword = true;
			}
			else
			{
				std::cout << "Mots de passe incorrecte" << std::endl;
				attempt--;
			}
		} while (attempt > 0 && !correctPassword);
	}
	~PasswodManager()
	{
	}

	bool Islocked()
	{
		return correctPassword;
	}
};

int main()
{
	PasswodManager *passwodManager = new PasswodManager();

	if (!passwodManager->Islocked())
	{
		std::cout << "succesfull acces to code" << std::endl;
	}
	else
	{
		std::cout << "acces denied" << std::endl;
	}

	delete passwodManager;
	system("pause");

	return EXIT_SUCCESS;
}