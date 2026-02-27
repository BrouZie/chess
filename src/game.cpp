#include "game.h"
#include <algorithm>
#include <iostream>

namespace
{
	// Helper: chess notation to Position
	Position chessToGrid(std::string_view input)
	{
		return Position { (input[1] - '1'), (input[0] - 'a') };
	}

	std::string gridToChess(Position pos)
	{
		std::string square {};
		square += static_cast<char>(pos.col + 'a');
		square += static_cast<char>(pos.row + '1');
		
		return square;
	}
}

// Initialize w/ standard chess positions
Game::Game()
	: m_board { Board::standardPosition() }
{
}

void Game::displayBoard() const { m_board.printBoard(); }

bool Game::tryMove(Position from, Position to)
{
  const Piece& piece { m_board.getPieceAt(from) };

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

void Game::displayLegalMoves(Position pos) const
{
	auto moves {getLegalMoves(pos)};

	std::cout << "Possible moves:\n";

	int choice {1};
	for (auto move : moves)
	{
		// char file = static_cast<char>(move.col + 'a');
		// char rank = static_cast<char>(move.row + '1');
		//
		// std::cout << choice << ": "<< file << rank << '\n';

		std::cout << choice << ": " << gridToChess(move) << '\n';
	 	++choice;
	}
}

void Game::init()
{
	displayBoard();

	std::cout << "Which piece would you like to move? ";
	std::string chosenPiece {};
	std::cin >> chosenPiece;

	displayLegalMoves(chessToGrid(static_cast<std::string_view>(chosenPiece)));

	std::cout << "Where would you like to move the piece? ";
	std::string newPos {};
	std::cin >> newPos;
	
	m_board.movePiece(chessToGrid(chosenPiece), chessToGrid(newPos));
}
