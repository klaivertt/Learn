#include "Common.h"
#include "Game.hpp"

class PasswordManager
{
private:
	int attempt = 5;
	bool isUnlocked = false;
	std::string secret = "";

public:
	PasswordManager() {};

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

	void EnterPassword(const std::string _password)
	{
		secret = _password;
	}

	void LoadPassword(const std::string _password)
	{
		secret = _password;
	}

	bool GetIsUnlocked() const
	{
		return isUnlocked;
	}
};

int main()
{
	// read	a file with the saved pasword if fille not exis create a file
	std::fstream file("password.txt", std::ios::in | std::ios::out | std::ios::app);
	if (!file.is_open())
	{
		std::cout << "error" << std::endl;
	}
	else
	{
		PasswordManager* passwordManager = new PasswordManager();
		// read if file is empty
		std::string line;
		if (!std::getline(file, line))
		{
			std::cout << "no password" << std::endl;

			std::string input;
			std::getline(std::cin, input);
			passwordManager->EnterPassword(input);
		}
		else
		{
			passwordManager->LoadPassword(line);
		}

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
	}