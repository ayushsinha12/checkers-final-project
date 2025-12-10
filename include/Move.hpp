#ifndef MOVE_HPP
#define MOVE_HPP

#include "Position.hpp"

struct Move {
    Position from;
    Position to;
    bool is_jump;

    Move() : from(), to(), is_jump(false) {}
    Move(const Position & f, const Position & t, bool jump)
        : from(f), to(t), is_jump(jump) {}
};

#endif