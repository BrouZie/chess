#include "board.h"
#include "pieces.h"
#include <iostream>
#include <vector>

Board::Board() { }

void Board::printBoard() const
{
  for (int row { 7 }; row >= 0; --row) {
    for (int col {}; col < 8; ++col) {
      std::cout << getPieceDisplay(row, col);
    }
    std::cout << '\n';
  }
}

std::string Board::getPieceDisplay(int row, int col) const
{
  const Piece& p = board[row][col];

  if (p.getType() == Piece::Type::empty) {
    return " \033[90m• ";
  }

  std::string display {};
  display += (p.getTeam() == Piece::Team::white) ? "\033[92m" : "\033[94m";

  switch (p.getType()) {
  case Piece::Type::pawn:
    display += " P ";
    break;
  case Piece::Type::knight:
    display += " N ";
    break;
  case Piece::Type::bishop:
    display += " B ";
    break;
  case Piece::Type::rook:
    display += " R ";
    break;
  case Piece::Type::queen:
    display += " Q ";
    break;
  case Piece::Type::king:
    display += " K ";
    break;
  default:
    std::cerr << "No valid type detected\n";
    break;
  }
  return display;
}

void Board::setPieceAt(int row, int col, Piece::Team team, Piece::Type type)
{
  board[row][col] = Piece(team, type, { row, col });
}

bool Board::isInBounds(Position pos) const
{
	return pos[0] >= 0 && pos[0] < boardSize && pos[1] >= 0 && pos[1] < boardSize;
}

bool Board::isEmptyAt(Position pos) const
{
	return board[pos[0]][pos[1]].getType() == Piece::Type::empty;
}

bool Board::isEnemyAt(Position pos, Piece::Team team) const
{
	const Piece& p {board[pos[0]][pos[1]]};
	return p.getType() != Piece::Type::empty && p.getTeam() != team;
}
