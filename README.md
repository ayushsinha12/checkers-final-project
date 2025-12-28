# Terminal Checkers (CS3520 Final Project)

A fully playable Checkers game that runs in the terminal. The game supports standard diagonal movement, capturing (jumps), king promotion, turn-taking, and win detection (when a player has no pieces left). The game functions exactly how a standard checkers game does.

---
## Features

- **8x8 checkers board** printed in the terminal with row/column indices.
- **Two players**: Red (`r` man, `R` king) vs Black (`b` man, `B` king).
- **Legal move validation**:
  - Pieces can only move diagonally to valid squares.
  - Captures remove opponent pieces correctly.
- **Jump capture support** (2-square diagonal moves remove the jumped piece).
- **King promotion**:
  - Red promotes upon reaching row `7`.
  - Black promotes upon reaching row `0`.
- **Game over detection**:
  - A winner is declared when the opponent has no pieces remaining.
- **Robust input handling**:
  - Invalid moves and out-of-bounds moves are rejected with clear error messages.
  - Input failure states are handled so the program does not get stuck repeating errors.









# cs3520-proj

## Instructions

Will Usher's SDL 2.0 Tutorial can be found here: https://www.willusher.io/pages/sdl2/.

This starter code has done Lesson 0.

The Makefile is set up to build all `.cpp` files in the `src` folder and create executables in `bin/main`.  To just build the release executable, run `make exe`.

General structure:
 * src: for source (.cpp) files, everything here will get compiled/linked (src/main.cpp provided)
 * test: for test source code (using CxxText, expected to be in extern/cxxtest-4.4)
 * include: for header (.hpp) files, looked in for #include
 * res: for resources (e.g. images)
 * build: where created intermediate (e.g. object) files go
 * bin: where created executables go
 * doc: where generated documentation (Doxygen) goes

Configurations:
 * rel: for speed
 * deb: for debugging
 * cov: for code coverage (with gcov)
 * prf: for performance analysis (with gprof)
