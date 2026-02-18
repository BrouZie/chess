#ifndef PIECES_H
#define PIECES_H

#include <array>
#include <vector>

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
		Piece(Team color, Type piece, std::array<int, 2> currentPos);

		void getMoves() const;
		Piece::Type getType() const { return m_piece; }
		Piece::Team getTeam() const { return m_color; }

	private:
		std::vector<std::array<int, 2>> knightMoves() const;	
	  std::vector<std::array<int, 2>> kingMoves() const;	
		std::vector<std::array<int, 2>> pawnMoves() const;
		std::vector<std::array<int, 2>> rookMoves() const;
		std::vector<std::array<int, 2>> bishopMoves() const;
		std::vector<std::array<int, 2>> queenMoves() const;
		std::vector<std::array<int, 2>> legalMoves(std::vector<std::array<int, 2>>& moves) const;
		void showMoves(std::vector<std::array<int, 2>> pieceMoves) const;

		Type m_piece {};
		Team m_color {};
		std::array<int, 2> m_currentPos {};

};

#endif 
