#include "Common.h"
int main()
{
    float length = 0.f;

    do
    {
        std::cout << "Entrez la longeur d'un coté d'un carre" << std::endl;
        std::cin >> length;
   
    } while (length <= 0.f);
   
    float perimeter = 0.f;

    perimeter = length * 4.f;

    std::cout << "Le perimettre du carrer est de : " << perimeter << std::endl;
    
	system("pause");
    return EXIT_SUCCESS;
}