#include "Common.h"
#include "Game.hpp"

class PasswordManager
{
private:
	int attempt = 5;
	bool isUnlocked = false;
	std::string secret = "Admin123";

public:
	PasswordManager();

	void AskForPassword()
	{
		std::string input;

		while (attempt > 0 && !isUnlocked)
		{
			std::cout << "Tentatives restantes : " << attempt << "\nSaisie : ";
			std::getline(std::cin, input);

			if (input == secret)
			{
				isUnlocked = true;
			}
			else
			{
				attempt--;
			}
		}
	}

	bool GetIsUnlocked() const
	{
		return isUnlocked;
	}
};

int main()
{
	PasswordManager *passwordManager = new PasswordManager();

	passwordManager->AskForPassword();

	if (!passwordManager->GetIsUnlocked())
	{
		std::cout << "succesfull acces to code" << std::endl;
	}
	else
	{
		std::cout << "acces denied" << std::endl;
	}

	delete passwordManager;
	system("pause");

	return EXIT_SUCCESS;
}