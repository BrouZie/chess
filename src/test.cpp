#include "pieces.h"


int main()
{
	Piece a { Piece::Team::white, Piece::Type::pawn, {0, 0} };
	a.getMoves();
}
