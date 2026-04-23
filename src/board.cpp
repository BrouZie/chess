#include "board.h"
#include "display.h"
#include <iostream>
#include <vector>

Board::Board()
{
}

Board Board::testPositions()
{
    Board board {};

    board.setPieceAt({ 0, 0 }, Piece::Team::white, Piece::Type::rook);
    board.setPieceAt({ 0, 1 }, Piece::Team::white, Piece::Type::knight);

    return board;
}

Board Board::standardPosition()
{
    Board board {};

    board.setPieceAt({ 0, 0 }, Piece::Team::white, Piece::Type::rook);
    board.setPieceAt({ 0, 1 }, Piece::Team::white, Piece::Type::knight);
    board.setPieceAt({ 0, 2 }, Piece::Team::white, Piece::Type::bishop);
    board.setPieceAt({ 0, 3 }, Piece::Team::white, Piece::Type::queen);
    board.setPieceAt({ 0, 4 }, Piece::Team::white, Piece::Type::king);
    board.setPieceAt({ 0, 5 }, Piece::Team::white, Piece::Type::bishop);
    board.setPieceAt({ 0, 6 }, Piece::Team::white, Piece::Type::knight);
    board.setPieceAt({ 0, 7 }, Piece::Team::white, Piece::Type::rook);

    for (int col {}; col < 8; ++col)
    {
        board.setPieceAt({ 1, col }, Piece::Team::white, Piece::Type::pawn);
    }

    for (int col {}; col < 8; ++col)
    {
        board.setPieceAt({ 6, col }, Piece::Team::black, Piece::Type::pawn);
    }

    board.setPieceAt({ 7, 0 }, Piece::Team::black, Piece::Type::rook);
    board.setPieceAt({ 7, 1 }, Piece::Team::black, Piece::Type::knight);
    board.setPieceAt({ 7, 2 }, Piece::Team::black, Piece::Type::bishop);
    board.setPieceAt({ 7, 3 }, Piece::Team::black, Piece::Type::queen);
    board.setPieceAt({ 7, 4 }, Piece::Team::black, Piece::Type::king);
    board.setPieceAt({ 7, 5 }, Piece::Team::black, Piece::Type::bishop);
    board.setPieceAt({ 7, 6 }, Piece::Team::black, Piece::Type::knight);
    board.setPieceAt({ 7, 7 }, Piece::Team::black, Piece::Type::rook);

    return board;
}

void Board::printBoard() const
{
    using namespace Display;

    auto printBoardLabels = []() {
        std::cout << boardIndent << "  ";
        for (char c { 'a' }; c <= 'h'; ++c)
        {
            std::cout << ' ' << colorGrey << c << colorReset << ' ';
        }
        std::cout << '\n';
    };

    for (int row { 7 }; row >= 0; --row)
    {
        int rank { row + 1 };
        std::cout << boardIndent << ' ' << colorGrey << rank << colorReset;
        for (int col {}; col < boardSize; ++col)
        {
            std::cout << getPieceDisplay(Position { row, col });
        }
        std::cout << '\n';
    }

    printBoardLabels();
}

std::string Board::getPieceDisplay(Position pos) const
{
    const Piece& p = m_grid[pos.row][pos.col];

    if (p.getType() == Piece::Type::empty)
    {
        return std::string(Display::emptySymbol);
    }

    std::string display {};
    display += Display::teamColors(p.getTeam());
    display += Display::pieceSymbol(p.getType());
    display += Display::colorReset;
    return display;
}

void Board::setPieceAt(Position pos, Piece::Team team, Piece::Type type)
{
    m_grid[pos.row][pos.col] = Piece(team, type);
}

const Piece& Board::getPieceAt(Position pos) const
{
    return m_grid[pos.row][pos.col];
}

Piece& Board::getPieceAt(Position pos)
{
    auto [row, col] = pos;
    return m_grid[row][col];
}

bool Board::isInBounds(Position pos) const
{
    return pos.row >= 0 && pos.row < boardSize && pos.col >= 0 && pos.col < boardSize;
}

bool Board::isEmptyAt(Position pos) const
{
    return m_grid[pos.row][pos.col].getType() == Piece::Type::empty;
}

bool Board::isEnemyAt(Position pos, Piece::Team team) const
{
    const Piece& p { m_grid[pos.row][pos.col] };
    return p.getType() != Piece::Type::empty && p.getTeam() != team;
}

std::vector<Position> Board::getLegalMoves(Position pos) const
{
    auto [row, col] = pos;
    const Piece& piece { m_grid[row][col] };

    switch (piece.getType())
    {
        case Piece::Type::knight: return getKnightMoves(pos, piece.getTeam());
        case Piece::Type::rook:   return getRookMoves(pos, piece.getTeam());
        case Piece::Type::bishop: return getBishopMoves(pos, piece.getTeam());
        case Piece::Type::queen:  return getQueenMoves(pos, piece.getTeam());
        case Piece::Type::king:   return getKingMoves(pos, piece.getTeam());
        case Piece::Type::pawn:   return getPawnMoves(pos, piece.getTeam());
        default:                  return {};
    }
}

std::vector<Position> Board::getKnightAttacks(Position pos, Piece::Team team) const
{
    auto [row, col] = pos;
    std::vector<Position> moves {};

    std::vector<Position> offsets { { 1, 2 },   { 2, 1 },   { 2, -1 }, { 1, -2 },
                                    { -1, -2 }, { -2, -1 }, { -2, 1 }, { -1, 2 } };

    for (const auto& [dr, dc] : offsets)
    {
        Position target { row + dr, col + dc };
        if (isInBounds(target) && (isEmptyAt(target) || isEnemyAt(target, team)))
        {
            moves.push_back(target);
        }
    }

    return moves;
}

std::vector<Position> Board::getKingAttacks(Position pos, Piece::Team team) const
{
    auto [row, col] = pos;
    std::vector<Position> moves {};

    std::vector<Position> offsets { { 0, 1 },  { 1, 1 },   { 1, 0 },  { 1, -1 },
                                    { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 } };

    for (const auto& [dr, dc] : offsets)
    {
        Position target { row + dr, col + dc };
        if (isInBounds(target) && (isEmptyAt(target) || isEnemyAt(target, team)))
        {
            moves.push_back(target);
        }
    }

    return moves;
}

std::vector<Position> Board::getBishopAttacks(Position pos, Piece::Team team) const
{
    auto [row, col] = pos;
    std::vector<Position> moves {};

    std::vector<Position> directions { { 1, 1 }, { 1, -1 }, { -1, -1 }, { -1, 1 } };

    for (const auto& [dr, dc] : directions)
    {
        Position current { row + dr, col + dc };

        while (isInBounds(current))
        {
            if (isEmptyAt(current))
            {
                moves.push_back(current);
            }
            else
            {
                if (isEnemyAt(current, team))
                    moves.push_back(current);
                break;
            }
            current.row += dr;
            current.col += dc;
        }
    }

    return moves;
}

std::vector<Position> Board::getQueenAttacks(Position pos, Piece::Team team) const
{
    auto [row, col] = pos;
    std::vector<Position> moves {};

    std::vector<Position> directions { { 1, 0 }, { -1, 0 }, { 0, 1 },   { 0, -1 },
                                       { 1, 1 }, { 1, -1 }, { -1, -1 }, { -1, 1 } };

    for (const auto& [dr, dc] : directions)
    {
        Position current { row + dr, col + dc };

        while (isInBounds(current))
        {
            if (isEmptyAt(current))
            {
                moves.push_back(current);
            }
            else
            {
                if (isEnemyAt(current, team))
                    moves.push_back(current);
                break;
            }
            current.row += dr;
            current.col += dc;
        }
    }

    return moves;
}

std::vector<Position> Board::getRookAttacks(Position pos, Piece::Team team) const
{
    auto [row, col] = pos;
    std::vector<Position> moves {};

    std::vector<Position> directions { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

    for (const auto& [dr, dc] : directions)
    {
        Position current { row + dr, col + dc };

        while (isInBounds(current))
        {
            if (isEmptyAt(current))
            {
                moves.push_back(current);
            }
            else
            {
                if (isEnemyAt(current, team))
                    moves.push_back(current);
                break;
            }
            current.row += dr;
            current.col += dc;
        }
    }

    return moves;
}

std::vector<Position> Board::getPawnAttacks(Position pos, Piece::Team team) const
{
    auto [row, col] = pos;
    std::vector<Position> moves {};

    int direction { (team == Piece::Team::white) ? 1 : -1 };

    // Diagonal captures
    for (int dc : { -1, 1 })
    {
        Position diag { row + direction, col + dc };
        if (isInBounds(diag) && isEnemyAt(diag, team))
        {
            moves.push_back(diag);
        }
    }

    return moves;
}

bool Board::isSquareAttacked(Position pos, Piece::Team team) const
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            const Piece& piece { getPieceAt({ row, col }) };
            if (piece.getType() == Piece::Type::empty || piece.getTeam() == team)
            {
                continue;
            }

            std::vector<Position> attackedSquares {};

            if (piece.getType() == Piece::Type::king)
            {
                attackedSquares = getKingAttacks({ row, col }, piece.getTeam());
            }
            else if (piece.getType() == Piece::Type::knight)
            {
                attackedSquares = getKnightAttacks({ row, col }, piece.getTeam());
            }
            else if (piece.getType() == Piece::Type::bishop)
            {
                attackedSquares = getBishopAttacks({ row, col }, piece.getTeam());
            }
            else if (piece.getType() == Piece::Type::queen)
            {
                attackedSquares = getQueenAttacks({ row, col }, piece.getTeam());
            }
            else if (piece.getType() == Piece::Type::rook)
            {
                attackedSquares = getRookAttacks({ row, col }, piece.getTeam());
            }
            else if (piece.getType() == Piece::Type::pawn)
            {
                attackedSquares = getPawnAttacks({ row, col }, piece.getTeam());
            }
            else
            {
                continue;
            }

            for (const Position& square : attackedSquares)
            {
                if (square == pos)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheck(Piece::Team team) const
{
    Position kingPos {};
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (getPieceAt({ row, col }).getType() == Piece::Type::king &&
                getPieceAt({ row, col }).getTeam() == team)
            {
                kingPos = { row, col };
            }
        }
    }

    return isSquareAttacked(kingPos, team);
}

std::vector<Position> Board::getKnightMoves(Position pos, Piece::Team team) const
{
    std::vector<Position> moves {};

    for (const Position& target : getKnightAttacks(pos, team))
    {
        Board copy = *this;
        copy.movePiece(pos, target);
        if (!copy.isCheck(team))
            moves.push_back(target);
    }

    return moves;
}

std::vector<Position> Board::getKingMoves(Position pos, Piece::Team team) const
{
    auto [row, col]   = pos;
    int backRank      = (team == Piece::Team::white) ? 0 : 7;
    const Piece& king = getPieceAt({ backRank, 4 });

    std::vector<Position> moves = getKingAttacks(pos, team);

    if (!king.getHasMoved())
    {
        const Piece& kingsideRook = getPieceAt({ backRank, 7 });
        if (kingsideRook.getType() == Piece::Type::rook && !kingsideRook.getHasMoved() &&
            isEmptyAt({ backRank, 5 }) && isEmptyAt({ backRank, 6 }) &&
            !isSquareAttacked({ backRank, 4 }, team) && !isSquareAttacked({ backRank, 5 }, team) &&
            !isSquareAttacked({ backRank, 6 }, team))
        {
            moves.push_back({ row, col + 2 });
        }

        const Piece& queensideRook = getPieceAt({ backRank, 0 });
        if (queensideRook.getType() == Piece::Type::rook && !queensideRook.getHasMoved() &&
            isEmptyAt({ backRank, 3 }) && isEmptyAt({ backRank, 2 }) &&
            isEmptyAt({ backRank, 1 }) && !isSquareAttacked({ backRank, 4 }, team) &&
            !isSquareAttacked({ backRank, 3 }, team) && !isSquareAttacked({ backRank, 2 }, team) &&
            !isSquareAttacked({ backRank, 1 }, team))
        {
            moves.push_back({ row, col - 2 });
        }
    }

    std::vector<Position> legalMoves {};
    for (const Position& target : moves)
    {
        Board copy = *this;
        copy.movePiece(pos, target);
        if (!copy.isCheck(team))
            legalMoves.push_back(target);
    }

    return legalMoves;
}

std::vector<Position> Board::getBishopMoves(Position pos, Piece::Team team) const
{
    std::vector<Position> moves {};

    for (const Position& target : getBishopAttacks(pos, team))
    {
        Board copy = *this;
        copy.movePiece(pos, target);
        if (!copy.isCheck(team))
            moves.push_back(target);
    }

    return moves;
}

std::vector<Position> Board::getQueenMoves(Position pos, Piece::Team team) const
{
    std::vector<Position> moves {};

    for (const Position& target : getQueenAttacks(pos, team))
    {
        Board copy = *this;
        copy.movePiece(pos, target);
        if (!copy.isCheck(team))
            moves.push_back(target);
    }

    return moves;
}

std::vector<Position> Board::getRookMoves(Position pos, Piece::Team team) const
{
    std::vector<Position> moves {};

    for (const Position& target : getRookAttacks(pos, team))
    {
        Board copy = *this;
        copy.movePiece(pos, target);
        if (!copy.isCheck(team))
            moves.push_back(target);
    }

    return moves;
}

std::vector<Position> Board::getPawnMoves(Position pos, Piece::Team team) const
{
    auto [row, col] = pos;
    std::vector<Position> moves {};

    int direction { (team == Piece::Team::white) ? 1 : -1 };
    int startRow { (team == Piece::Team::white) ? 1 : 6 };

    // Forward one
    Position oneAhead { row + direction, col };
    if (isInBounds(oneAhead) && isEmptyAt(oneAhead))
    {
        moves.push_back(oneAhead);

        // Forward two (only if one ahead was empty AND on starting row)
        Position twoAhead { row + 2 * direction, col };
        if (row == startRow && isInBounds(twoAhead) && isEmptyAt(twoAhead))
        {
            moves.push_back(twoAhead);
        }
    }

    std::vector<Position> attacks { getPawnAttacks(pos, team) };
    moves.insert(moves.end(), attacks.begin(), attacks.end());

    std::vector<Position> legalMoves {};
    for (const Position& target : moves)
    {
        Board copy = *this;
        copy.movePiece(pos, target);
        if (!copy.isCheck(team))
            legalMoves.push_back(target);
    }

    return legalMoves;
}

bool Board::movePiece(Position from, Position to)
{
    auto [fromRow, fromCol] = from;
    auto [toRow, toCol]     = to;

    Piece& piece { m_grid[fromRow][fromCol] }; // Should maybe change to getPieceAt function
    if (piece.getType() == Piece::Type::empty)
        return false;

    if (piece.getType() == Piece::Type::king)
    {
        int backRank = (piece.getTeam() == Piece::Team::white) ? 0 : 7;

        if (to.col - from.col == 2) // kingside
        {
            Piece& kingsideRook = getPieceAt({ backRank, 7 });
            kingsideRook.setHasMoved(true);
            m_grid[backRank][5] = kingsideRook;
            m_grid[backRank][7] = Piece();
        }
        if (to.col - from.col == -2) // queenside
        {
            Piece& queensideRook = getPieceAt({ backRank, 0 });
            queensideRook.setHasMoved(true);
            m_grid[backRank][3] = queensideRook;
            m_grid[backRank][0] = Piece();
        }
    }

    piece.setHasMoved(true);
    m_grid[toRow][toCol]     = piece;
    m_grid[fromRow][fromCol] = Piece(); // empty piece
    return true;
}
