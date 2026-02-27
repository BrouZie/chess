#include "game.h"
#include <iostream>

int main()
{
	Game game;

	while(true)
	{
		std::cout << "Press 'n' to exit\n";
		char userInput {};
		std::cin >> userInput;

		if (userInput == 'n')
			break;

		game.init();
	}

	return 0;
}
