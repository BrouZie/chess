#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game {
public:
		Game();
		void displayBoard() const;
		bool tryMove(Position from, Position to);
		std::vector<Position> getLegalMoves(Position pos) const;

private:
		Board m_board;
		Piece::Team m_currentTurn { Piece::Team::white };
		void initializePieces();
};

#endif
