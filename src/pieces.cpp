#include "pieces.h"

Piece::Piece()
		: m_color { Team::white }
		, m_piece { Type::empty }
{
}

Piece::Piece(Team color, Type piece)
			: m_color { color }
			, m_piece { piece }
{
}
