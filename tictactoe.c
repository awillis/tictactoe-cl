//
// Created by alan on 12/23/16.
//

#include <stdint.h>
#include "tictactoe.h"

/*
 * To check a win, go to each space, and see if it contains an X or an O
 * If it contains either X or O, check the eight directions around the space
 * to see if they also contain the same selection.
 * If the current space and a space in a particular direction match,
 * enter recursive function to check the matching space and direction
 * to find the next match in that direction. The number of spaces needed for a win
 * should be passed to this function.
 */

enum winner check_win_condition(struct Board *board) {

    enum winner winr = NONE;

    for (uint8_t x = 0; x < board->border.xpos; x++ ) {
        for (uint8_t y = 0; y < board->border.ypos; y++) {

            struct Square current_space = board->grid[x][y];

            if ((current_space.state != EMPTY) || (current_space.state != BORDER)) {
                for (int direction = 0; direction < 8; direction++) {

                    winr = find_winner(&current_space, direction, board->win_squares);

                    if ( winr > 0 ) {
                        break;
                    }
                }
            }
        }
    }
    return winr;
}

enum winner find_winner(const struct Square *current_space, int direction, int win_squares) {

    win_squares--;

    // return if we have a winner
    if ( win_squares == 0 ) {
        return (enum winner) current_space->state;
    }

    // continue if the next space matches
    if ((current_space->state == current_space->compass[direction]->state)) {
        find_winner(current_space->compass[direction], direction, win_squares);
    }

    return NONE;
}