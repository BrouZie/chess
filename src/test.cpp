#include "game.h"
#include <iostream>

int main()
{
	Game game;
	std::cout << "Write 'exit' if you want to exit the program!\n";

	while(game.init())
	{
		game.init();
	}

	std::cout << "Thanks for playing (:\n";

	return 0;
}
