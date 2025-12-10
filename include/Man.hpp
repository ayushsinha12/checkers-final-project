#ifndef MAN_HPP
#define MAN_HPP

#include "Piece.hpp"

class Man : public Piece {
public:
    Man(PieceColor c);
    virtual ~Man();

    virtual std::list<Move> get_moves(const Board & board,
                                      const Position & pos) const;
    virtual char symbol() const;
};

#endif