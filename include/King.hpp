#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
public:
    King(PieceColor c);
    virtual ~King();

    virtual std::list<Move> get_moves(const Board & board,
                                      const Position & pos) const;
    virtual char symbol() const;
};

#endif