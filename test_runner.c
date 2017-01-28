//
// Created by alan on 12/23/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DEBUG 0

typedef struct {
    char player;
    int xpos;
    int ypos;
} Move;

typedef struct {
    int num_lines;
    char **lines;
    int num_moves;
    Move **moves;
    int board_lines;
    char **board;
} TestCase;


char* move_asprintf(Move* move) {
    char *buff = NULL;
    asprintf(&buff, "Move{player=%c (%d,%d)}", move->player, move->xpos, move->ypos);
    return buff;
}

Move* parse_move(char* s) {
    Move* move = calloc(1, sizeof(Move));
    move->player = s[0];

    char* num_start = strchr(s, ',');
    num_start++;
    char* num_end = strchr(num_start+1, ',');
    move->xpos = atoi(num_start);

    num_start = num_end+1;
    move->ypos = atoi(num_start);
    return move;
}


TestCase* test_case_load_from_file(const char* test_file) {
    TestCase* test_case = (TestCase*)calloc(1, sizeof(TestCase));
    if (DEBUG) {
        printf("%s: test file: %s\n", __PRETTY_FUNCTION__, test_file);
    }

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(test_file, "r");
    if (fp == NULL) {
        perror("Error opening test_file! ");
        exit(errno);
    }

    int reading_moves = 1;
    while((read = getline(&line, &len, fp)) != -1) {
        *strchr(line, '\n') = '\0';
        if (DEBUG) {
            printf("%s: read num_lines=%d line=%s\n", __PRETTY_FUNCTION__, test_case->num_lines, line);
        }
        test_case->num_lines++;
        test_case->lines = realloc(test_case->lines, test_case->num_lines * sizeof(char**));
        test_case->lines[test_case->num_lines-1] = line;

        if ('-' == line[0]) {
            reading_moves = 0;
            line = NULL;
            len = 0;
            continue;
        }

        if (reading_moves) {
            test_case->num_moves++;
            test_case->moves = realloc(test_case->moves, test_case->num_moves * sizeof(char**));
            test_case->moves[test_case->num_moves-1] = parse_move(line);
        }

        if (!reading_moves) {
            test_case->board_lines++;
            test_case->board = realloc(test_case->board, test_case->board_lines * sizeof(char**));
            test_case->board[test_case->board_lines-1] = line;
        }

        line = NULL;
        len = 0;
    }

    fclose(fp);

    return test_case;
}

void test_case_print(const TestCase* test_case) {
    printf("TestCase{\n");

    /*
    printf("  num_lines: %d\n", test_case->num_lines);
    for (int ii = 0; ii < test_case->num_lines; ++ii) {
        printf("  line[%d]: %s\n", ii, test_case->lines[ii]);
    }
    */

    printf("  num_moves: %d\n", test_case->num_moves);
    for (int ii = 0; ii < test_case->num_moves; ++ii) {
        char* move_str = move_asprintf(test_case->moves[ii]);
        printf("  move[%d]: %s\n", ii, move_str);
        free(move_str);
    }

    printf("  board_lines: %d\n", test_case->board_lines);
    for (int ii = 0; ii < test_case->board_lines; ++ii) {
        printf("  board[%d]: %s\n", ii, test_case->board[ii]);
    }
    printf("}\n");
}

int run_test_file(const char* test_file) {
    printf("%s: test file: %s\n", __PRETTY_FUNCTION__, test_file);

    TestCase *test_case = test_case_load_from_file(test_file);
    test_case_print(test_case);

    return 0;
}

int main(int argc, char** argv) {
    printf("let's run some tests!\n");
    for (int ii = 1; ii < argc; ++ii) {
        run_test_file(argv[ii]);
    }
    return 0;
}

