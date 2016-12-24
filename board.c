//
// Created by alan on 12/23/16.
//

#include <stdint.h>
#include "tictactoe.h"

// Initializes a new board game
struct Board new_board(uint8_t rows, uint8_t columns, ...)
{
    struct Board board;
    struct Square border = { .xpos = rows, .ypos = columns, .state = BORDER };
    board.border = border;

    // Create empty grid
    for (uint8_t x = 0; x < rows; x++) {
        for (uint8_t y = 0; y < columns; y++) {
            struct Square s = { x, y, EMPTY };
            board.grid[x][y] = s;
        }
    }

    // Link squares to one another
    for (uint8_t x = 0; x < rows; x++) {
        for (uint8_t y = 0; y < columns; y++) {

            struct Square* s = &board.grid[x][y];
            int north = y + 1, east = x + 1;
            int south = y - 1, west = x - 1;

            // north border check
            if (board.border.ypos == north) {
                s->compass[North] = &board.border;
            }
            else
            {
                s->compass[North] = &board.grid[x][north];
            }

            // northeast border check
            if ((board.border.ypos == north) || (board.border.xpos == east)) {
                s->compass[NEast] = &board.border;
            }
            else
            {
                s->compass[NEast] = &board.grid[east][north];
            }

            // east border check
            if (board.border.xpos == east) {
                s->compass[East] = &board.border;
            }
            else
            {
                s->compass[East] = &board.grid[east][y];
            }

            // south east border check
            if ((board.border.xpos == east) || (south < 0)) {
                s->compass[SEast] = &board.border;
            }
            else
            {
                s->compass[SEast] = &board.grid[east][south];
            }

            // south border check
            if (south < 0) {
                s->compass[South] = &board.border;
            } else {
                s->compass[South] = &board.grid[x][south];
            }

            // south west border check
            if ((south < 0) || (west < 0)) {
                s->compass[SWest] = &board.border;
            }
            else
            {
                s->compass[SWest] = &board.grid[west][south];
            }

            // west border check
            if (west < 0) {
                s->compass[West] = &board.border;
            }
            else
            {
                s->compass[West] = &board.grid[west][y];
            }

            // north west border check
            if ((board.border.ypos == north) || (west < 0)) {
                s->compass[NWest] = &board.border;
            }
            else
            {
                s->compass[NWest] = &board.grid[west][north];
            }
        }
    }

    return board;
}
