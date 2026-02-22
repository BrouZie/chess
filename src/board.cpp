#include "board.h"
#include "display.h"
#include <iostream>
#include <vector>

Board::Board() { }

void Board::printBoard() const
{
	auto printBoardLabels = []()
	{
		std::cout << Display::boardIndent << "  ";
		for (char c{'a'}; c <= 'h'; ++c) { std::cout << ' ' << c << ' '; }
		std::cout << '\n';
	};

  for (int row { 7 }; row >= 0; --row)
	{
		int rank { row + 1 };
		std::cout << Display::boardIndent << ' ' << rank;
    for (int col {}; col < boardSize; ++col)
		{
      std::cout << getPieceDisplay(row, col);
    }
		std::cout << '\n';
  }

	printBoardLabels();
}

std::string Board::getPieceDisplay(int row, int col) const
{
  const Piece& p = board[row][col];

  if (p.getType() == Piece::Type::empty) {
    return std::string(Display::emptySymbol);
  }

  std::string display {};
	display += Display::teamColors(p.getTeam());
	display += Display::pieceSymbol(p.getType());
	display += Display::colorReset;
  return display;
}

void Board::setPieceAt(int row, int col, Piece::Team team, Piece::Type type)
{
  board[row][col] = Piece(team, type);
}

const Piece& Board::getPieceAt(int row, int col) const
{
	return board[row][col];
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

std::vector<Position> Board::getLegalMoves(Position pos) const
{
		auto [row, col] = pos;
		const Piece& piece { board[row][col] };

		switch (piece.getType())
		{
				case Piece::Type::knight: return getKnightMoves(pos, piece.getTeam());
				case Piece::Type::rook: return getRookMoves(pos, piece.getTeam());
				case Piece::Type::bishop: return getBishopMoves(pos, piece.getTeam());
				case Piece::Type::queen: return getQueenMoves(pos, piece.getTeam());
				case Piece::Type::king: return getKingMoves(pos, piece.getTeam());
				case Piece::Type::pawn: return getPawnMoves(pos, piece.getTeam());
				default: return {};
		}
}

std::vector<Position> Board::getKnightMoves(Position pos, Piece::Team team) const
{
	auto [row, col] = pos;
	std::vector<Position> moves {};

	std::vector<Position> offsets {
		{1, 2}, {2, 1}, {2, -1}, {1, -2},
		{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
	};

	for (const auto& [dr, dc] : offsets)
	{
		Position target { row + dr, col + dc };
		if (isInBounds(target) && (isEmptyAt(target) || isEnemyAt(target, team)))
		{
			moves.push_back(target);
		}
	}

	return moves;
}

std::vector<Position> Board::getKingMoves(Position pos, Piece::Team team) const
{
	auto [row, col] = pos;
	std::vector<Position> moves {};

	std::vector<Position> offsets {
		{0, 1}, {1, 1}, {1, 0}, {1, -1},
		{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
	};

	for (const auto& [dr, dc] : offsets)
	{
		Position target { row + dr, col + dc };
		if (isInBounds(target) && (isEmptyAt(target) || isEnemyAt(target, team)))
		{
			moves.push_back(target);
		}
	}

	return moves;
}

std::vector<Position> Board::getRookMoves(Position pos, Piece::Team team) const
{
	auto [row, col] = pos;
	std::vector<Position> moves {};

	std::vector<Position> directions { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	for (const auto& [dr, dc] : directions)
	{
		Position current { row + dr, col + dc };

		while (isInBounds(current))
		{
			if (isEmptyAt(current))
			{
				moves.push_back(current);
			}
			else
			{
				if (isEnemyAt(current, team))
					moves.push_back(current);
				break;
			}
			current[0] += dr;
			current[1] += dc;
		}
	}

	return moves;
}

std::vector<Position> Board::getBishopMoves(Position pos, Piece::Team team) const
{
	auto [row, col] = pos;
	std::vector<Position> moves {};

	std::vector<Position> directions { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };

	for (const auto& [dr, dc] : directions)
	{
		Position current { row + dr, col + dc };

		while (isInBounds(current))
		{
			if (isEmptyAt(current))
			{
				moves.push_back(current);
			}
			else
			{
				if (isEnemyAt(current, team))
					moves.push_back(current);
				break;
			}
			current[0] += dr;
			current[1] += dc;
		}
	}

	return moves;
}

std::vector<Position> Board::getQueenMoves(Position pos, Piece::Team team) const
{
	auto [row, col] = pos;
	std::vector<Position> moves {};

  std::vector<Position> directions {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1},
      {1, 1}, {1, -1}, {-1, -1}, {-1, 1}
  };

	for (const auto& [dr, dc] : directions)
	{
		Position current { row + dr, col + dc };

		while (isInBounds(current))
		{
			if (isEmptyAt(current))
			{
				moves.push_back(current);
			}
			else
			{
				if (isEnemyAt(current, team))
					moves.push_back(current);
				break;
			}
			current[0] += dr;
			current[1] += dc;
		}
	}

	return moves;
}

std::vector<Position> Board::getPawnMoves(Position pos, Piece::Team team) const
{
	auto [row, col] = pos;
	std::vector<Position> moves {};

	int direction { (team == Piece::Team::white) ? 1 : -1 };
	int startRow { (team == Piece::Team::white) ? 1 : 6 };

	// Forward one
	Position oneAhead { row + direction, col };
	if (isInBounds(oneAhead) && isEmptyAt(oneAhead))
	{
		moves.push_back(oneAhead);

		// Forward two (only if one ahead was empty AND on starting row)
		Position twoAhead { row + 2 * direction, col };
		if (row == startRow && isInBounds(twoAhead) && isEmptyAt(twoAhead))
		{
			moves.push_back(twoAhead);
		}
	}

	// Diagonal captures
	for (int dc : {-1, 1})
	{
		Position diag { row + direction, col + dc };
		if (isInBounds(diag) && isEnemyAt(diag, team))
		{
			moves.push_back(diag);
		}
	}

	return moves;
}

bool Board::movePiece(Position from, Position to)
{
	auto [fromRow, fromCol] = from;
	auto [toRow, toCol] = to;

	const Piece& piece { board[fromRow][fromCol] };
	if (piece.getType() == Piece::Type::empty)
		return false;

	board[toRow][toCol] = Piece(piece.getTeam(), piece.getType());
	board[fromRow][fromCol] = Piece(); // empty piece
	return true;
}
