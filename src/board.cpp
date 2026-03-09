#include "board.h"
#include "display.h"
#include <iostream>
#include <vector>

Board::Board() { }

Board Board::standardPosition()
{
	Board board {};

  board.setPieceAt({0, 0}, Piece::Team::white, Piece::Type::rook);
  board.setPieceAt({0, 1}, Piece::Team::white, Piece::Type::knight);
  board.setPieceAt({0, 2}, Piece::Team::white, Piece::Type::bishop);
  board.setPieceAt({0, 3}, Piece::Team::white, Piece::Type::queen);
  board.setPieceAt({0, 4}, Piece::Team::white, Piece::Type::king);
  board.setPieceAt({0, 5}, Piece::Team::white, Piece::Type::bishop);
  board.setPieceAt({0, 6}, Piece::Team::white, Piece::Type::knight);
  board.setPieceAt({0, 7}, Piece::Team::white, Piece::Type::rook);

  for (int col {}; col < 8; ++col)
  {
    board.setPieceAt({1, col}, Piece::Team::white, Piece::Type::pawn);
  }

  for (int col {}; col < 8; ++col)
  {
    board.setPieceAt({6, col}, Piece::Team::black, Piece::Type::pawn);
  }

  board.setPieceAt({7, 0}, Piece::Team::black, Piece::Type::rook);
  board.setPieceAt({7, 1}, Piece::Team::black, Piece::Type::knight);
  board.setPieceAt({7, 2}, Piece::Team::black, Piece::Type::bishop);
  board.setPieceAt({7, 3}, Piece::Team::black, Piece::Type::queen);
  board.setPieceAt({7, 4}, Piece::Team::black, Piece::Type::king);
  board.setPieceAt({7, 5}, Piece::Team::black, Piece::Type::bishop);
  board.setPieceAt({7, 6}, Piece::Team::black, Piece::Type::knight);
  board.setPieceAt({7, 7}, Piece::Team::black, Piece::Type::rook);

	return board;
}

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
      std::cout << getPieceDisplay(Position { row, col} );
    }
		std::cout << '\n';
  }

	printBoardLabels();
}

std::string Board::getPieceDisplay(Position pos) const
{
  const Piece& p = m_grid[pos.row][pos.col];

  if (p.getType() == Piece::Type::empty) {
    return std::string(Display::emptySymbol);
  }

  std::string display {};
	display += Display::teamColors(p.getTeam());
	display += Display::pieceSymbol(p.getType());
	display += Display::colorReset;
  return display;
}

void Board::setPieceAt(Position pos, Piece::Team team, Piece::Type type)
{
  m_grid[pos.row][pos.col] = Piece(team, type);
}

const Piece& Board::getPieceAt(Position pos) const
{
	return m_grid[pos.row][pos.col];
}

bool Board::isInBounds(Position pos) const
{
	return pos.row >= 0 && pos.row < boardSize && pos.col >= 0 && pos.col < boardSize;
}

bool Board::isEmptyAt(Position pos) const
{
	return m_grid[pos.row][pos.col].getType() == Piece::Type::empty;
}

bool Board::isEnemyAt(Position pos, Piece::Team team) const
{
	const Piece& p {m_grid[pos.row][pos.col]};
	return p.getType() != Piece::Type::empty && p.getTeam() != team;
}

std::vector<Position> Board::getLegalMoves(Position pos) const
{
		auto [row, col] = pos;
		const Piece& piece { m_grid[row][col] };

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

	Position startPos { (team == Piece::Team::white) ? Position{0, 4} : Position{-1, 4} };
	bool hasMoved { false };

	std::vector<Position> offsets {
		{0, 1}, {1, 1}, {1, 0}, {1, -1},
		{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
	};
	if (pos != startPos)
	{
		hasMoved = true;
	}

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
	std::array<Position, 2> startPos { (team == Piece::Team::white) ? {Position{0, 0}, Position{0, 7}} : {Position{-1, 0}, Position{-1, 7}} };

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
			current.row += dr;
			current.col += dc;
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
			current.row += dr;
			current.col += dc;
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
			current.row += dr;
			current.col += dc;
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

	const Piece& piece { m_grid[fromRow][fromCol] };
	if (piece.getType() == Piece::Type::empty)
		return false;

	m_grid[toRow][toCol] = Piece(piece.getTeam(), piece.getType());
	m_grid[fromRow][fromCol] = Piece(); // empty piece
	return true;
}
