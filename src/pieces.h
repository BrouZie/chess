#ifndef PIECES_H
#define PIECES_H

#include <array>

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
		Piece(Team color, Type piece);

		Piece::Type getType() const { return m_piece; }
		Piece::Team getTeam() const { return m_color; }
		bool getHasMoved() const { return m_hasMoved; }
		void setHasMoved(bool moved) { m_hasMoved = moved; }

	private:
		Type m_piece {};
		Team m_color {};
		bool m_hasMoved { false };
};

#endif 
