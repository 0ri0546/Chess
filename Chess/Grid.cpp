#include "Grid.hpp"

void Grid::reset()
{
    board.fill(Piece::None);

    for (int x = 0; x < SIZE; ++x)
    {
        set(x, 1, Piece::PawnWhite);
        set(x, 6, Piece::PawnBlack);
    }

    set(0, 0, Piece::RookWhite); set(7, 0, Piece::RookWhite);
    set(0, 7, Piece::RookBlack); set(7, 7, Piece::RookBlack);

    set(1, 0, Piece::KnightWhite); set(6, 0, Piece::KnightWhite);
    set(1, 7, Piece::KnightBlack); set(6, 7, Piece::KnightBlack);

    set(2, 0, Piece::BishopWhite); set(5, 0, Piece::BishopWhite);
    set(2, 7, Piece::BishopBlack); set(5, 7, Piece::BishopBlack);

    set(3, 0, Piece::QueenWhite);
    set(3, 7, Piece::QueenBlack);

    set(4, 0, Piece::KingWhite);
    set(4, 7, Piece::KingBlack);
}

Piece Grid::get(int x, int y) const
{
    return board[y * SIZE + x];
}

void Grid::set(int x, int y, Piece piece)
{
    board[y * SIZE + x] = piece;
}
