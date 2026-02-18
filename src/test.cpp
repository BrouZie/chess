#include "pieces.h"


int main()
{
	Piece knight { Piece::Team::white, Piece::Type::queen, {0, 0} };
	knight.getMoves();
}
