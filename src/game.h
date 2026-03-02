#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game
{
public:
  Game();
  void displayBoard() const;
  bool tryMove(Position from, Position to);
  std::vector<Position> getLegalMoves(Position pos) const;
	void displayLegalMoves(Position pos) const;
	Piece::Team getCurrentTurn() { return m_currentTurn; }
	bool init();

private:
  Board m_board;
  Piece::Team m_currentTurn { Piece::Team::white };
};

#endif
