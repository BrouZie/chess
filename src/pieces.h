#ifndef PIECES_H
#define PIECES_H

#include <array>
#include <vector>

class Piece
{
	public:
		enum class Type
		{
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

		Piece(Team color, Type piece, std::array<int, 2> currentPos);

		void getMoves() const;

	private:
		std::vector<std::array<int, 2>> knightMoves() const;	

		Type m_piece {};
		Team m_color {};
		std::array<int, 2> m_currentPos {};

};

#endif 
