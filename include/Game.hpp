#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"

class Game {
private:
    Board board;
    PieceColor current_turn;
    bool game_over;
public:
    Game();

    // Main loop of the game
    void run();
private:
    void print_turn_info() const;
    void handle_player_input();
    bool check_game_over();
};

#endif