#include "game.h"
#include <iostream>
#include <limits>

int main()
{
	Game game;

	while(true)
	{
		std::cout << "Press 'n' to exit\n";
		char input {};
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		game.init();
	}

	return 0;
}
