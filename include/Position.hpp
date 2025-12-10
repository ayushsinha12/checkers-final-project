#ifndef POSITION_HPP
#define POSITION_HPP

struct Position {
    int row;
    int col;

    Position() : row(0), col(0) {}
    Position(int r, int c) : row(r), col(c) {}
};

#endif