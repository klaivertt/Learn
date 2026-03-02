#include "Common.h"
#include "Geometry.hpp"

enum class State
{
	SQUARE,
	RECTANGLE,
	NB_SHAPE,

	NONE = -1,
};

// @param string _messsage countain wha do you want the user choise
float AskPositiveNumber(const std::string& _message)
{
	float tempNumber = 0.f;
	do
	{
		std::cout << _message << " : ";
		std::cin >> tempNumber;
		std::cout << std::endl;
	} while (tempNumber <= 0.f);
	return tempNumber;
}

State ChoiseState()
{
	int choice = -1;
	do
	{
		std::cout << "0 : Calculer l'aire d'un carrer" << std::endl;
		std::cout << "1 : Calculer l'aire d'un rectangle" << std::endl;
		std::cout << "Entre un nombre entre 0 et 1 pour selectionner" << std::endl;
		std::cin >> choice;
	} while (choice > (static_cast<int>(State::NB_SHAPE)-1) || choice < static_cast<int>(State::SQUARE));

	return static_cast<State>(choice);
}


void DisplayResult(std::string _mesage, float _result)
{
	std::cout << _mesage << _result << std::endl;
}

int main()
{
	float width = 0.f;
	float height = 0.f;

	State choice = ChoiseState();

	switch (choice)
	{
	case State::SQUARE:
	{
		DisplayResult("L'aire du carrer est de : ", CalculateSquareArea(AskPositiveNumber("Entrez la longueur du carrer")));
		break;
	}
	case State::RECTANGLE:
	{
		DisplayResult("L'aire du rectangle est de : ", CalculateRectangleArea(AskPositiveNumber("Entrez la longueur d'un rectangle"), AskPositiveNumber("Entrez la largeur d'un rectangle")));
		break;
	}
	default:
		std::cout << "Pas de state" << std::endl;
		break;
	}

	system("pause");
	return EXIT_SUCCESS;
}