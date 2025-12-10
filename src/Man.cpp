#include "Man.hpp"
#include "Board.hpp"

Man::Man(PieceColor c) : Piece(c) {}

Man::~Man() {}

std::list<Move> Man::get_moves(const Board & board,
                               const Position & pos) const {
    std::list<Move> moves;

    int dir = (color == COLOR_RED) ? 1 : -1;
    int r = pos.row;
    int c = pos.col;

    int dr = dir;
    int dc;
    for (dc = -1; dc <= 1; dc += 2) {
        int nr = r + dr;
        int nc = c + dc;
        if (board.is_inside(nr, nc) && board.get_piece(nr, nc) == 0) {
            Move m(pos, Position(nr, nc), false);
            moves.push_back(m);
        }
        int jr = r + 2 * dr;
        int jc = c + 2 * dc;
        int mr = r + dr;
        int mc = c + dc;
        if (board.is_inside(jr, jc) && board.get_piece(jr, jc) == 0) {
            Piece * mid = board.get_piece(mr, mc);
            if (mid != 0 && mid->get_color() != color) {
                Move jump_move(pos, Position(jr, jc), true);
                moves.push_back(jump_move);
            }
        }
    }

    return moves;
}

char Man::symbol() const {
    return (color == COLOR_RED) ? 'r' : 'b';
}