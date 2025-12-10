#ifndef BOARD_HPP
#define BOARD_HPP

#include <list>
#include "Position.hpp"
#include "Move.hpp"
#include "Exceptions.hpp"
#include "Piece.hpp"

class Man;
class King;

// Board manages an 8x8 grid of Piece
class Board {
private:
    Piece * grid[8][8];

    // Disable copying.
    Board(const Board &);
    Board & operator=(const Board &);

public:
    Board();
    ~Board();

    bool is_inside(int row, int col) const;

    Piece * get_piece(int row, int col) const;
    void set_piece(int row, int col, Piece * piece);

    // Either executes a move or throws on error
    void move_piece(const Move & move);

    // Prints the current board state (uses a temp 2D char array – concept A)
    void print() const;
    void print_with_temp() const;

    bool has_pieces(PieceColor color) const;
    std::list<Move> get_all_moves(PieceColor color) const;
};

#endif