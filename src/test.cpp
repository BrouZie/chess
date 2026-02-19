#include "pieces.h"


int main()
{
	Piece knight { Piece::Team::white, Piece::Type::queen, {1, 1} };
	knight.getMoves();
}
