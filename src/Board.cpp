#include "Board.hpp"
#include "Man.hpp"
#include "King.hpp"
#include <iostream>

// Helper function for concept A: function taking a 2D built-in array.
static void print_temp_board(char temp[8][8]) {
    std::cout << "    0 1 2 3 4 5 6 7" << std::endl;
    std::cout << "   -----------------" << std::endl;
    int row;
    int col;
    for (row = 0; row < 8; ++row) {
        std::cout << row << " | ";
        for (col = 0; col < 8; ++col) {
            std::cout << temp[row][col] << ' ';
        }
        std::cout << std::endl;
    }
}

Board::Board() {
    int r, c;
    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            grid[r][c] = 0;
        }
    }

    // Initial setup where red pieces on rows 0,1,2 and black pieces on rows 5,6,7
    for (r = 0; r < 3; ++r) {
        for (c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 1) {
                grid[r][c] = new Man(COLOR_RED); // concept H: new
            }
        }
    }

    for (r = 5; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 1) {
                grid[r][c] = new Man(COLOR_BLACK); // concept H: new
            }
        }
    }
}

Board::~Board() {
    int r, c;
    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            delete grid[r][c]; // concept H: delete
            grid[r][c] = 0;
        }
    }
}

bool Board::is_inside(int row, int col) const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

Piece * Board::get_piece(int row, int col) const {
    if (!is_inside(row, col)) {
        return 0;
    }
    return grid[row][col];
}

void Board::set_piece(int row, int col, Piece * piece) {
    if (!is_inside(row, col)) {
        throw OutOfBoundsException("set_piece: position is out of bounds");
    }
    grid[row][col] = piece;
}

void Board::move_piece(const Move & move) {
    if (!is_inside(move.from.row, move.from.col) ||
        !is_inside(move.to.row, move.to.col)) {
        throw OutOfBoundsException("Move coordinates out of bounds");
    }

    Piece * p = get_piece(move.from.row, move.from.col);
    if (p == 0) {
        throw InvalidMoveException("No piece at source position");
    }

    if (get_piece(move.to.row, move.to.col) != 0) {
        throw InvalidMoveException("Destination is not empty");
    }

    // Check that this move is in the piece's legal moves list
    std::list<Move> legal = p->get_moves(*this, move.from);
    std::list<Move>::const_iterator it = legal.begin();
    bool found = false;
    for (; it != legal.end(); ++it) {
        if (it->to.row == move.to.row &&
            it->to.col == move.to.col) {
            found = true;
            break;
        }
    }
    if (!found) {
        throw InvalidMoveException("Move is not legal for this piece");
    }

    // If this is a jump, remove the captured piece
    int drow = move.to.row - move.from.row;
    // int dcol = move.to.col - move.from.col;
    int abs_drow = drow;
    if (abs_drow < 0) {
        abs_drow = -abs_drow;
    }

    if (abs_drow == 2) { // jump
        int mid_row = (move.from.row + move.to.row) / 2;
        int mid_col = (move.from.col + move.to.col) / 2;
        Piece * captured = get_piece(mid_row, mid_col);
        if (captured != 0) {
            delete captured;
            grid[mid_row][mid_col] = 0;
        }
    }

    // Moves the piece
    grid[move.to.row][move.to.col] = p;
    grid[move.from.row][move.from.col] = 0;

    // Upgraded to King
    // Red promotes when reaching row 7 and black promotes when reaching row 0
    Man * man_ptr = dynamic_cast<Man *>(p);
    if (man_ptr != 0) {
        if ((p->get_color() == COLOR_RED && move.to.row == 7) ||
            (p->get_color() == COLOR_BLACK && move.to.row == 0)) {
            PieceColor c = p->get_color();
            delete p;
            grid[move.to.row][move.to.col] = new King(c);
        }
    }
}

void Board::print_with_temp() const {
    char temp[8][8];
    int r, c;
    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            if (grid[r][c] == 0) {
                temp[r][c] = '.';
            } else {
                temp[r][c] = grid[r][c]->symbol();
            }
        }
    }
    // Concept A: passing a built-in 2D array to a function.
    print_temp_board(temp);
}

void Board::print() const {
    print_with_temp();
}

bool Board::has_pieces(PieceColor color) const {
    int r, c;
    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            if (grid[r][c] != 0 &&
                grid[r][c]->get_color() == color) {
                return true;
            }
        }
    }
    return false;
}

std::list<Move> Board::get_all_moves(PieceColor color) const {
    std::list<Move> all;
    int r, c;
    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            Piece * p = grid[r][c];
            if (p != 0 && p->get_color() == color) {
                Position pos(r, c);
                std::list<Move> moves = p->get_moves(*this, pos);
                std::list<Move>::const_iterator it = moves.begin();
                for (; it != moves.end(); ++it) {
                    all.push_back(*it); // STL container not vector/string (list) – concept J
                }
            }
        }
    }
    return all;
}