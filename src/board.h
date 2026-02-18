#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include <array>
#include <string>

class Board {
public:
  Board();
  void printBoard() const;
  void setPieceAt(int row, int col, Piece::Team team, Piece::Type type);

private:
	std::array<std::array<Piece, 8>, 8> board{};
	// board[0][col] = bottom row
	// board[7][col] = top row

  std::string getPieceDisplay(int row, int col) const;
};

#endif
