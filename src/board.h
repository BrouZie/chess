#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include <array>
#include <string>
#include <vector>

class Board {
public:
  Board();
  void printBoard() const;
  void setPieceAt(int row, int col, Piece::Team team, Piece::Type type);

	std::vector<Position> getLegalMoves(Position pos) const;
	bool movePiece(Position from, Position to);

private:
	static constexpr int boardSize {8};

	std::array<std::array<Piece, boardSize>, boardSize> board{};
	// board[0][col] = bottom row
	// board[7][col] = top row

	std::vector<Position> getPawnMoves(Position pos, Piece::Team team) const;
	std::vector<Position> getKnightMoves(Position pos, Piece::Team team) const;
	std::vector<Position> getKingMoves(Position pos, Piece::Team team) const;
	std::vector<Position> getRookMoves(Position pos, Piece::Team team) const;
	std::vector<Position> getBishopMoves(Position pos, Piece::Team team) const;
	std::vector<Position> getQueenMoves(Position pos, Piece::Team team) const;

	bool isInBounds(Position pos) const;
	bool isEmptyAt(Position pos) const;
	bool isEnemyAt(Position pos, Piece::Team team) const;

  std::string getPieceDisplay(int row, int col) const;
};

#endif
