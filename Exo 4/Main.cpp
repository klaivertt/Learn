#include "Common.h"
#include "Game.hpp"

class PasswordManager
{
private:
	int attempt = 5;
	bool isUnlocked = false;
	std::string secret = "";
	std::fstream file;
	std::string path;
public:
	PasswordManager(const std::string _path)
	{
		path = _path;
	};

	void EnterPassword()
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

	void AskForPassword()
	{
		if (OpenFiles(path))
		{
			std::string line;
			if (!std::getline(file, line))
			{
				file.close();
				std::cout << "no password" << std::endl;
				std::cout << "Enter a password :";
				WriteInFiles(path);				
			}
			else
			{
				SavePassword(line);
				file.close(); 
			}

			EnterPassword();
		}
	}

	void WriteInFiles(const std::string _path)
	{
		std::ofstream file(_path, std::ios::app);
		std::string input;
		std::getline(std::cin, input);
		SavePassword(input);
		file << input << std::endl;
		file.close();
	}

	bool OpenFiles(const std::string _path)
	{
		file = std::fstream(_path, std::ios::in);

		if (!file.is_open())
		{
			std::cout << "error, file does Exist" << std::endl;
			return false;
		}
		else
		{
			return true;
		}
	}

	void SavePassword(const std::string _password)
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

	PasswordManager* passwordManager = new PasswordManager("password.txt");


	passwordManager->AskForPassword();

	if (passwordManager->GetIsUnlocked())
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