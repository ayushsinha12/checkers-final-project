#include "Piece.hpp"

Piece::Piece(PieceColor c) : color(c) {}

Piece::~Piece() {}

PieceColor Piece::get_color() const {
    return color;
}

bool Piece::is_red() const {
    return color == COLOR_RED;
}