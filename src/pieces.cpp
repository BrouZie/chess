#include "pieces.h"
#include "iostream"
#include <cstddef>

Piece::Piece()
		: m_piece { Type::empty }
		, m_color { Team::white }
		, m_currentPos { 0, 0 }
{
}

Piece::Piece(Team color, Type piece, std::array<int, 2> currentPos)
			: m_piece { piece }
			, m_currentPos { currentPos }
			, m_color { color }
			{
			}


void Piece::getMoves() const
{
	switch(m_piece)
	{
		case Piece::Type::pawn:
		{
			showMoves(pawnMoves());
			break;
		}
		case Piece::Type::knight:
		{
			showMoves(knightMoves());
			break;
		}
		case Piece::Type::king:
		{
			showMoves(kingMoves());
			break;
		}
	}
}


std::vector<std::array<int, 2>> Piece::pawnMoves() const
{
	std::vector<std::array<int, 2>> moves {
		{m_currentPos[0], m_currentPos[1]+1},
	};

	return legalMoves(moves);
}


std::vector<std::array<int, 2>> Piece::knightMoves() const
{
	std::vector<std::array<int, 2>> moves {
		{m_currentPos[0]+1, m_currentPos[1]+2},
		{m_currentPos[0]+2, m_currentPos[1]+1},
		{m_currentPos[0]+2, m_currentPos[1]-1},
		{m_currentPos[0]+1, m_currentPos[1]-2},
		{m_currentPos[0]-1, m_currentPos[1]-2},
		{m_currentPos[0]-2, m_currentPos[1]-1},
		{m_currentPos[0]-2, m_currentPos[1]+1},
		{m_currentPos[0]-1, m_currentPos[1]+2}
	};

	return legalMoves(moves);
}


std::vector<std::array<int, 2>> Piece::kingMoves() const
{
	std::vector<std::array<int, 2>> moves {
		{m_currentPos[0], m_currentPos[1]+1},
		{m_currentPos[0]+1, m_currentPos[1]+1},
		{m_currentPos[0]+1, m_currentPos[1]},
		{m_currentPos[0]+1, m_currentPos[1]-1},
		{m_currentPos[0], m_currentPos[1]-1},
		{m_currentPos[0]-1, m_currentPos[1]-1},
		{m_currentPos[0]-1, m_currentPos[1]},
		{m_currentPos[0]-1, m_currentPos[1]+1}
	};

	return legalMoves(moves);
}


std::vector<std::array<int, 2>> Piece::legalMoves(std::vector<std::array<int, 2>>& pieceMoves) const
{
	std::vector<std::array<int, 2>> allLegalMoves {};

	for (const std::array<int, 2>& move : pieceMoves)
		{
			if (move[0] <= 7 && move[0] >= 0 && move[1] <= 7 && move[1] >= 0)
			{
				allLegalMoves.push_back(move);
			}
		}

	return allLegalMoves;
}


void Piece::showMoves(std::vector<std::array<int, 2>> pieceMoves) const
{
	for (std::size_t index { 0 }; index < pieceMoves.size(); index++)
	{
		std::cout << pieceMoves[index][0] << " " << pieceMoves[index][1] << '\n';
	}
}
