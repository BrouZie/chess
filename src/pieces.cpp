#include "pieces.h"

Piece::Piece()
		: m_color { Team::white }
		, m_piece { Type::empty }
		, m_currentPos { 0, 0 }
{
}

Piece::Piece(Team color, Type piece, Position currentPos)
			: m_color { color }
			, m_piece { piece }
			, m_currentPos { currentPos }
{
}
