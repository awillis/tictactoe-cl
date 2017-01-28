//
// Created by alan on 12/23/16.
//

#include <stdio.h>
#include "tictactoe.h"

int main() {

    printf("Let's play Tic Tac Toe!\n");
    struct Board game;
    game = new_board(9, 9, 6);
    enum winner w;

    do {
        w = check_win_condition(&game);
    } while (w == NONE);

    // getchar();
    return 0;
}
