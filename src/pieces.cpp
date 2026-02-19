#include "pieces.h"
#include <iostream>
#include <cstddef>
#include <set>

Piece::Piece()
		: m_color { Team::white }
		, m_piece { Type::empty }
		, m_currentPos { 0, 0 }
{
}

Piece::Piece(Team color, Type piece, std::array<int, 2> currentPos)
			: m_color { color }
			, m_piece { piece }
			, m_currentPos { currentPos }
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
		case Piece::Type::rook:
		{
			showMoves(rookMoves());
			break;
		}
		case Piece::Type::bishop:
		{
			showMoves(bishopMoves());
			break;
		}
		case Piece::Type::queen:
		{
			showMoves(queenMoves());
			break;
		}
		case Piece::Type::empty:
		{
			std::cout << "Empty\n";
			break;
		}
		default:
		{
			std::cout << "????";
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

std::vector<std::array<int, 2>> Piece::rookMoves() const
{
	std::vector<std::array<int, 2>> allLegalMoves {};
	int xPos { m_currentPos[0] };
	int yPos { m_currentPos[1] };

	for (int xCurrent {xPos + 1}; xCurrent < 8; xCurrent++)
	{
		allLegalMoves.push_back({xCurrent, yPos});
	}

	for (int xCurrent {xPos - 1}; xCurrent >= 0; xCurrent--)
	{
		allLegalMoves.push_back({xCurrent, yPos});
	}

	for (int yCurrent {yPos + 1}; yCurrent < 8; yCurrent++)
	{
		allLegalMoves.push_back({xPos, yCurrent});
	}

	for (int yCurrent {yPos - 1}; yCurrent >= 0; yCurrent--)
	{
		allLegalMoves.push_back({xPos, yCurrent});
	}


	return allLegalMoves;
}

std::vector<std::array<int, 2>> Piece::bishopMoves() const
{
	std::vector<std::array<int, 2>> allLegalMoves {};
	int xPos { m_currentPos[0] };
	int yPos { m_currentPos[1] };

	for (int xCurrent { xPos + 1 }, yCurrent { yPos + 1 }; xCurrent < 8 && yCurrent < 8; xCurrent++, yCurrent++)
	{
		allLegalMoves.push_back({xCurrent, yCurrent});
	}

	for (int xCurrent { xPos + 1 }, yCurrent { yPos - 1 }; xCurrent < 8 && yCurrent >= 0; xCurrent++, yCurrent--)
	{
		allLegalMoves.push_back({xCurrent, yCurrent});
	}

	for (int xCurrent { xPos - 1 }, yCurrent { yPos - 1 }; xCurrent >= 0 && yCurrent >= 0; xCurrent--, yCurrent--)
	{
		allLegalMoves.push_back({xCurrent, yCurrent});
	}

	for (int xCurrent { xPos - 1 }, yCurrent { yPos + 1 }; xCurrent >= 0 && yCurrent < 8; xCurrent--, yCurrent++)
	{
		allLegalMoves.push_back({xCurrent, yCurrent});
	}

	return allLegalMoves;
}

std::vector<std::array<int, 2>> Piece::queenMoves() const
{
	std::vector<std::array<int, 2>> allLegalMoves {};
	int xPos { m_currentPos[0] };
	int yPos { m_currentPos[1] };

	for (int xCurrent { xPos + 1 }, yCurrent { yPos + 1 }; xCurrent < 8 && yCurrent < 8; xCurrent++, yCurrent++)
	{
		allLegalMoves.push_back({xCurrent, yCurrent});
	}

	for (int xCurrent { xPos + 1 }, yCurrent { yPos - 1 }; xCurrent < 8 && yCurrent >= 0; xCurrent++, yCurrent--)
	{
		allLegalMoves.push_back({xCurrent, yCurrent});
	}

	for (int xCurrent { xPos - 1 }, yCurrent { yPos - 1 }; xCurrent >= 0 && yCurrent >= 0; xCurrent--, yCurrent--)
	{
		allLegalMoves.push_back({xCurrent, yCurrent});
	}

	for (int xCurrent { xPos - 1 }, yCurrent { yPos + 1 }; xCurrent >= 0 && yCurrent < 8; xCurrent--, yCurrent++)
	{
		allLegalMoves.push_back({xCurrent, yCurrent});
	}

	for (int xCurrent {xPos + 1}; xCurrent < 8; xCurrent++)
	{
		allLegalMoves.push_back({xCurrent, yPos});
	}

	for (int xCurrent {xPos - 1}; xCurrent >= 0; xCurrent--)
	{
		allLegalMoves.push_back({xCurrent, yPos});
	}

	for (int yCurrent {yPos + 1}; yCurrent < 8; yCurrent++)
	{
		allLegalMoves.push_back({xPos, yCurrent});
	}

	for (int yCurrent {yPos - 1}; yCurrent >= 0; yCurrent--)
	{
		allLegalMoves.push_back({xPos, yCurrent});
	}

	return allLegalMoves;
}

std::vector<std::array<int, 2>> Piece::legalMoves(const std::vector<std::array<int, 2>>& pieceMoves) const
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


void Piece::showMoves(const std::vector<std::array<int, 2>>& pieceMoves) const
{
	for (std::size_t index { 0 }; index < pieceMoves.size(); index++)
	{
		std::cout << pieceMoves[index][0] << " " << pieceMoves[index][1] << '\n';
	}
}
