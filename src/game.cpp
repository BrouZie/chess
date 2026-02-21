#include "game.h"
#include <algorithm>

// Places "empty pieces" in 2D grid
Game::Game() { initializePieces(); }

// Places pieces on the board
void Game::initializePieces()
{
  m_board.setPieceAt(0, 0, Piece::Team::white, Piece::Type::rook);
  m_board.setPieceAt(0, 1, Piece::Team::white, Piece::Type::knight);
  m_board.setPieceAt(0, 2, Piece::Team::white, Piece::Type::bishop);
  m_board.setPieceAt(0, 3, Piece::Team::white, Piece::Type::queen);
  m_board.setPieceAt(0, 4, Piece::Team::white, Piece::Type::king);
  m_board.setPieceAt(0, 5, Piece::Team::white, Piece::Type::bishop);
  m_board.setPieceAt(0, 6, Piece::Team::white, Piece::Type::knight);
  m_board.setPieceAt(0, 7, Piece::Team::white, Piece::Type::rook);

  for (int col {}; col < 8; ++col)
  {
    m_board.setPieceAt(1, col, Piece::Team::white, Piece::Type::pawn);
  }

  for (int col {}; col < 8; ++col)
  {
    m_board.setPieceAt(6, col, Piece::Team::black, Piece::Type::pawn);
  }

  m_board.setPieceAt(7, 0, Piece::Team::black, Piece::Type::rook);
  m_board.setPieceAt(7, 1, Piece::Team::black, Piece::Type::knight);
  m_board.setPieceAt(7, 2, Piece::Team::black, Piece::Type::bishop);
  m_board.setPieceAt(7, 3, Piece::Team::black, Piece::Type::queen);
  m_board.setPieceAt(7, 4, Piece::Team::black, Piece::Type::king);
  m_board.setPieceAt(7, 5, Piece::Team::black, Piece::Type::bishop);
  m_board.setPieceAt(7, 6, Piece::Team::black, Piece::Type::knight);
  m_board.setPieceAt(7, 7, Piece::Team::black, Piece::Type::rook);
}

void Game::displayBoard() const { m_board.printBoard(); }

bool Game::tryMove(Position from, Position to)
{
  auto [row, col] = from;
  const Piece& piece { m_board.getPieceAt(row, col) };

  if (piece.getType() == Piece::Type::empty)
    return false;

  if (piece.getTeam() != m_currentTurn)
    return false;

  auto moves { m_board.getLegalMoves(from) };
  if (std::find(moves.begin(), moves.end(), to) == moves.end())
    return false;

  m_board.movePiece(from, to);

  m_currentTurn = (m_currentTurn == Piece::Team::white) ? Piece::Team::black : Piece::Team::white;

  return true;
}

std::vector<Position> Game::getLegalMoves(Position pos) const
{
	return m_board.getLegalMoves(pos);
}
