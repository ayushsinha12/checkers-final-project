#include "Game.hpp"
#include <iostream>

Game::Game()
    : board(), current_turn(COLOR_RED), game_over(false) {}

void Game::print_turn_info() const {
    std::cout << "Current turn: "
              << (current_turn == COLOR_RED ? "Red (r/R)" : "Black (b/B)")
              << std::endl;
}

bool Game::check_game_over() {
    if (!board.has_pieces(COLOR_RED)) {
        std::cout << "Black wins! Red has no pieces left." << std::endl;
        game_over = true;
        return true;
    }
    if (!board.has_pieces(COLOR_BLACK)) {
        std::cout << "Red wins! Black has no pieces left." << std::endl;
        game_over = true;
        return true;
    }

    std::list<Move> moves = board.get_all_moves(current_turn);
    if (moves.empty()) {
        if (current_turn == COLOR_RED) {
            std::cout << "Red has no legal moves. Black wins!" << std::endl;
        } else {
            std::cout << "Black has no legal moves. Red wins!" << std::endl;
        }
        game_over = true;
        return true;
    }

    return false;
}

void Game::handle_player_input() {
    int fr, fc, tr, tc;
    std::cout << "Enter move as: from_row from_col to_row to_col (0-7 indices)." << std::endl;
    std::cout << "Or enter -1 to quit." << std::endl;
    std::cout << "> ";
    std::cin >> fr;
    if (!std::cin) {
        throw InvalidMoveException("Failed to read input");
    }
    if (fr == -1) {
        game_over = true;
        std::cout << "Game ended by user." << std::endl;
        return;
    }
    std::cin >> fc >> tr >> tc;
    if (!std::cin) {
        throw InvalidMoveException("Failed to read input");
    }

    if (!board.is_inside(fr, fc) || !board.is_inside(tr, tc)) {
        throw OutOfBoundsException("Input coordinates out of bounds");
    }

    Piece * p = board.get_piece(fr, fc);
    if (p == 0) {
        throw InvalidMoveException("No piece at the given source square");
    }
    if (p->get_color() != current_turn) {
        throw InvalidMoveException("You must move your own piece");
    }

    Move move(Position(fr, fc), Position(tr, tc), false);
    board.move_piece(move);

    current_turn = (current_turn == COLOR_RED) ? COLOR_BLACK : COLOR_RED;
}

void Game::run() {
    std::cout << "Welcome to Terminal Checkers!" << std::endl;
    std::cout << "Red pieces: r (man), R (king)" << std::endl;
    std::cout << "Black pieces: b (man), B (king)" << std::endl;

    while (!game_over) {
        board.print();
        print_turn_info();

        if (check_game_over()) {
            break;
        }

        try {
            handle_player_input();
        } catch (const OutOfBoundsException & e) {
            std::cout << "OutOfBoundsException: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } catch (const InvalidMoveException & e) {
            std::cout << "InvalidMoveException: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } catch (const std::exception & e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    std::cout << "Thanks for playing!" << std::endl;
}