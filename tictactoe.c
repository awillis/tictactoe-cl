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

enum winner check_win(struct Board* board) {

    for (uint8_t x = 0; x < board->border.xpos; x++ ) {
        for (uint8_t y = 0; y < board->border.ypos; y++) {

            struct Square current_space = board->grid[x][y];

            if (current_space.state != EMPTY) {
                check_win_recursive(&current_space, board->win_squares);
            }
        }
    }
}

enum winner check_win_recursive(const struct Square* current_space, int win_squares) {

    if ((current_space->state == X) || (current_space->state == O)) {
        for (int direction = 0; direction < 8; direction++) {
            if ((current_space->compass[direction]->state == X) || current_space->compass[direction]->state == O) {

            }
        }
    }


}