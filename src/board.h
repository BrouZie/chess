#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Board {
	public:
		Board();
		void printBoard();
	private:
		int board[8][8]{};
};

#endif
