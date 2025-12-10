#ifndef PIECE_HPP
#define PIECE_HPP

#include <list>
#include "Position.hpp"
#include "Move.hpp"

class Board; // a forward declaration

enum PieceColor {
    COLOR_RED,
    COLOR_BLACK
};

class Piece {
protected:
    PieceColor color;
public:
    Piece(PieceColor c);
    virtual ~Piece();

    PieceColor get_color() const;
    bool is_red() const;

    // Gets all the legal moves for this piece based off a given position
    virtual std::list<Move> get_moves(const Board & board,
                                      const Position & pos) const = 0;

    // Symbol to print on the board
    virtual char symbol() const = 0;
};

#endif