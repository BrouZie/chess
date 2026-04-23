#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include <array>
#include <string>
#include <vector>

struct Position
{
    int row {};
    int col {};
    bool operator==(const Position& other) const
    {
        return row == other.row && col == other.col;
    }
    bool operator!=(const Position& other) const
    {
        return row != other.row || col != other.col;
    }
};

class Board
{
  public:
    Board();
    static Board standardPosition();
    static Board testPositions();
    void printBoard() const;
    void setPieceAt(Position pos, Piece::Team team, Piece::Type type);
    const Piece& getPieceAt(Position pos) const;
    Piece& getPieceAt(Position pos);

    std::vector<Position> getLegalMoves(Position pos) const;
    bool movePiece(Position from, Position to);

  private:
    static constexpr int boardSize { 8 };

    std::array<std::array<Piece, boardSize>, boardSize> m_grid {};

    std::vector<Position> getPawnMoves(Position pos, Piece::Team team) const;
    std::vector<Position> getKnightMoves(Position pos, Piece::Team team) const;
    std::vector<Position> getKingMoves(Position pos, Piece::Team team) const;
    std::vector<Position> getRookMoves(Position pos, Piece::Team team) const;
    std::vector<Position> getBishopMoves(Position pos, Piece::Team team) const;
    std::vector<Position> getQueenMoves(Position pos, Piece::Team team) const;

    std::vector<Position> getKingAttacks(Position pos, Piece::Team team) const;
    std::vector<Position> getKnightAttacks(Position pos, Piece::Team team) const;
    std::vector<Position> getBishopAttacks(Position pos, Piece::Team team) const;
    std::vector<Position> getQueenAttacks(Position pos, Piece::Team team) const;
    std::vector<Position> getRookAttacks(Position pos, Piece::Team team) const;
    std::vector<Position> getPawnAttacks(Position pos, Piece::Team team) const;

    bool isInBounds(Position pos) const;
    bool isEmptyAt(Position pos) const;
    bool isEnemyAt(Position pos, Piece::Team team) const;
    bool isSquareAttacked(Position pos, Piece::Team team) const;
    bool isCheck(Piece::Team team) const;

    std::string getPieceDisplay(Position pos) const;
};

#endif
