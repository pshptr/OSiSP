#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <opencl-c-base.h>
#include <stdbool.h>

#define BOARD_SIZE 3

void read_socket(int socket, void *buffer, size_t length);
void write_socket(int socket, const void *buffer, size_t length);
void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]);
void print_board(const char board[BOARD_SIZE][BOARD_SIZE]);
int make_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int column, char mark);
int make_computer_move(char board[BOARD_SIZE][BOARD_SIZE], char mark);
//bool check_win(const char board[BOARD_SIZE][BOARD_SIZE], char mark);

#endif  // GAME_LOGIC_H
