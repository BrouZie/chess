#ifndef PIECES_H
#define PIECES_H

#include <array>

using Position = std::array<int, 2>;

class Piece
{
	public:
		enum class Type
		{
			empty,
			pawn,
			knight,
			bishop,
			rook,
			queen,
			king
		};

		enum class Team
		{
			white,
			black
		};

		Piece(); // default constructor
		Piece(Team color, Type piece, Position currentPos);

		Piece::Type getType() const { return m_piece; }
		Piece::Team getTeam() const { return m_color; }

	private:
		Type m_piece {};
		Team m_color {};
		Position m_currentPos {};
};

#endif 
