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
		case Piece::Type::pawn:	std::cout << "Pawn";
		case Piece::Type::knight: 
		{
			std::vector<std::array<int, 2>> moves { Piece::knightMoves() };
			for (std::size_t index {0}; index < moves.size(); index++)	
			{
				std::cout << moves[index][0] << " " << moves[index][1] << '\n';
			}
		}
	}
}

std::vector<std::array<int, 2>> Piece::knightMoves() const
{
	std::vector<std::array<int, 2>> moves {{m_currentPos[0]+1, m_currentPos[1]+2}, 
																				{m_currentPos[0]+2, m_currentPos[1]+1}, 
																				{m_currentPos[0]+2, m_currentPos[1]-1},
																				{m_currentPos[0]+1, m_currentPos[1]-2},
																				{m_currentPos[0]-1, m_currentPos[1]-2},
																				{m_currentPos[0]-2, m_currentPos[1]-1},
																				{m_currentPos[0]-2, m_currentPos[1]+1},
																				{m_currentPos[0]-1, m_currentPos[1]+2}
																				};
	return moves;
}
