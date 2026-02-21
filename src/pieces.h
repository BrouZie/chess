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

		// void getMoves() const;
		Piece::Type getType() const { return m_piece; }
		Piece::Team getTeam() const { return m_color; }
		Position getPiece() const { return m_currentPos; }

	private:
		// std::vector<Position> knightMoves() const;	
		//  std::vector<Position> kingMoves() const;	
		// std::vector<Position> pawnMoves() const;
		// std::vector<Position> rookMoves() const;
		// std::vector<Position> bishopMoves() const;
		// std::vector<Position> queenMoves() const;
		// std::vector<Position> legalMoves(const std::vector<Position>& moves) const;
		// void showMoves(const std::vector<Position>& pieceMoves) const;

		Type m_piece {};
		Team m_color {};
		Position m_currentPos {};

};

#endif 
