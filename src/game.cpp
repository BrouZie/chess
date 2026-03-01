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

	std::string_view teamToString(Piece::Team team)
	{
		switch(team)
		{
			case Piece::Team::white: return "white";
			case Piece::Team::black: return "black";
			default: return "???";
		}

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
	std::cout << teamToString(getCurrentTurn()) << "'s turn:\n";

	displayBoard();
	std::string chosenPiece {};

	while (true)
	{
		std::cout << "Which piece would you like to move? ";
		while (true)
		{
			std::getline(std::cin, chosenPiece);
			chosenPiece.erase(std::remove(chosenPiece.begin(), chosenPiece.end(), ' '), chosenPiece.end());

			if (chosenPiece.size() == 2)
			{
				char file { chosenPiece[0] };
				char rank { chosenPiece[1] };

				if (file >= 'a' && file <= 'h'
						&& rank >= '1' && rank <= '8')
				{
					break;
				}

				else
				{
					std::cout << "The format is wrong! The first character should be from a-h and second should be from 1-8.\n";
				}
			}
		}

		displayLegalMoves(chessToGrid(static_cast<std::string_view>(chosenPiece)));
		if (m_board.getLegalMoves(chessToGrid(chosenPiece)).size() > 0)
		{
			break;
		}
		else
		{
			std::cout << "Choose a valid square!\n";
		}
	}

	std::cout << "Where would you like to move the piece? \n";
	std::string newPos {};
	std::cin >> newPos;
	
	tryMove(chessToGrid(chosenPiece), chessToGrid(newPos));
}
