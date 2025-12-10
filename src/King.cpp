#include "King.hpp"
#include "Board.hpp"

King::King(PieceColor c) : Piece(c) {}

King::~King() {}

std::list<Move> King::get_moves(const Board & board,
                                const Position & pos) const {
    std::list<Move> moves;

    int r = pos.row;
    int c = pos.col;

    int dr;
    for (dr = -1; dr <= 1; dr += 2) {
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
    }

    return moves;
}

char King::symbol() const {
    return (color == COLOR_RED) ? 'R' : 'B';
}