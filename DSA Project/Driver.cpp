#include "globalFunctions.h"
#include <iostream>

int main()
{
	system("color 79");

	char choice;
	
	displayMainMenu(choice);
	
	while(1)
	{
		displayStudentOrAdmin(choice);
		std::cin.get();
		std::cin.get();
	}

	system("pause");
	return 0;
}