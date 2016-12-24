//
// Created by alan on 12/23/16.
//

#include <stdio.h>
#include "tictactoe.h"

void main()
{
    printf("Let's play Tic Tac Toe!\n");
    struct Board game;
    game = new_board(64, 64, 6);
    enum winner w;

    do {
        check_win(&game);
    } while (w == NONE);

    getchar();
}