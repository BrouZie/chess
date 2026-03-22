#ifndef DISPLAY_H
#define DISPLAY_H

#include "pieces.h"
#include <string_view>

namespace Display
{
	constexpr std::string_view colorWhite = "\033[92m"; // green
	constexpr std::string_view colorBlack = "\033[94m"; // blue
	constexpr std::string_view colorGrey = "\033[90m"; // grey
	constexpr std::string_view colorReset = "\033[0m"; // white

	constexpr std::string_view boardIndent = "";

	constexpr std::string_view emptySymbol = " • ";
	constexpr std::string_view pawnSymbol = " P ";
	constexpr std::string_view knightSymbol = " N ";
	constexpr std::string_view kingSymbol = " K ";
	constexpr std::string_view queenSymbol = " Q ";
	constexpr std::string_view rookSymbol = " R ";
	constexpr std::string_view bishopSymbol = " B ";

	constexpr std::string_view pieceSymbol(Piece::Type type) {
		switch (type)
		{
			case Piece::Type::empty: return emptySymbol;
			case Piece::Type::pawn: return pawnSymbol;
			case Piece::Type::knight: return knightSymbol;
			case Piece::Type::king: return kingSymbol;
			case Piece::Type::queen: return queenSymbol;
			case Piece::Type::rook: return rookSymbol;
			case Piece::Type::bishop: return bishopSymbol;
		}
		return emptySymbol; // unreachable
	}

	constexpr std::string_view teamColors(Piece::Team team)
	{
		switch (team)
		{
			case Piece::Team::black: return colorBlack;
			case Piece::Team::white: return colorWhite;
		}
		return colorReset; // unreachable
	}
}

#endif
