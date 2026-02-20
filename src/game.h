#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game {
public:
		Game();
		void displayBoard() const;

private:
		Board m_board;
		void initializePieces();
};

#endif
