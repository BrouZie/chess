#include "game.h"
#include <iostream>

int main()
{
	Game game { Board::testPositions() };
	game.displayBoard();

	std::cout << "\n";

	if (game.tryMove({1, 1}, {2, 1}))
	{
		game.displayBoard();
		std::cout << "Move successful!\n";
	}
	else
		std::cout << "Failed! Illegal move!\n";

	return 0;
}
