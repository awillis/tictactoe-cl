//
// Created by alan on 12/23/16.
//

#include <stdint.h>

#define MAXROWS 9
#define MAXCOLS 9

enum sqstat
{
    EMPTY, X, O, BORDER
};

enum legend
{
    North,
    NEast,
    East,
    SEast,
    South,
    SWest,
    West,
    NWest
};

struct Square
{
    int xpos;
    int ypos;
    enum sqstat state;
    struct Square* compass[8];
};

struct Board
{
    int win_squares;
    struct Square grid[MAXROWS][MAXCOLS];
    struct Square border;
};

struct Board new_board(uint8_t rows, uint8_t columns, ...);

enum winner
{
    NONE, playerX, playerO
};

enum winner check_win_condition(struct Board *board);
enum winner find_winner(const struct Square *current_space, int direction, int win_squares);